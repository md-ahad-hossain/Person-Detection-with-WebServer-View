/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <WiFi.h>
#include <WiFiManager.h>

#include "app_camera_esp.h"
#include "esp_camera.h"
#include "main_functions.h"

#include "detection_responder.h"
#include "image_provider.h"

#include "model_settings.h"
#include "person_detect_model_data.h"

#include <TFLIteMicro.h>
#include <utility.h>

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <esp_timer.h>
#include <esp_log.h>
#include "esp_main.h"

// Globals
namespace {
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

// In order to use optimized tensorflow lite kernels, a signed int8_t quantized
// model is preferred over the legacy unsigned model format. This means that
// throughout this project, input images must be converted from unisgned to
// signed format. The easiest and quickest way to convert from unsigned to
// signed 8-bit integers is to subtract 128 from the unsigned value to get a
// signed value.

#ifdef CONFIG_IDF_TARGET_ESP32S3
constexpr int scratchBufSize = 70 * 1024;
#else
constexpr int scratchBufSize = 0;
#endif
// An area of memory to use for input, output, and intermediate arrays.
constexpr int kTensorArenaSize = 81 * 1024 + scratchBufSize;

static uint8_t *tensor_arena;//[kTensorArenaSize]; // Maybe we should move this to external
}  // namespace

void init_wifi() {
    WiFiManager wm;

    // যদি ESP reset হয়ে আবার আসে, auto connect চেষ্টা করবে
    if (!wm.autoConnect("PersonCam_Setup", "12345678")) {
        Serial.println("Failed to connect WiFi and hit timeout");
        ESP.restart();
    }
    Serial.println("WiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    // নেটওয়ার্ক স্ট্যাক স্থির হওয়ার জন্য ১–২ সেকেন্ড অপেক্ষা
    delay(1500);
}

void startCameraServer();

// The name of this function is important for Arduino compatibility.
void setup() {

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  delay(1000);

  // Camera init via wrapper
  if (InitCamera() != kTfLiteOk) {
      Serial.println("Camera initialization failed! Halting...");
      while (true) { vTaskDelay(1000); }
  }

  setupAlarmPin();       // এলার্ম পিন ইনিশিয়ালাইজ  
  init_wifi();          // WiFi connect
  startCameraServer(); // WebServer start

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_person_detect_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.printf("Model provided is schema version %d not equal to supported version %d.\n",
                  model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Allocate tensor arena
  if (tensor_arena == NULL) {
    tensor_arena = (uint8_t *) heap_caps_malloc(kTensorArenaSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  }
  if (tensor_arena == NULL) {
    Serial.printf("Couldn't allocate memory of %d bytes\n", kTensorArenaSize);
    return;
  }

  // Ops resolver
  static tflite::MicroMutableOpResolver<5> micro_op_resolver;
  micro_op_resolver.AddAveragePool2D();
  micro_op_resolver.AddConv2D();
  micro_op_resolver.AddDepthwiseConv2D();
  micro_op_resolver.AddReshape();
  micro_op_resolver.AddSoftmax();

  // Build interpreter
  static tflite::MicroInterpreter static_interpreter(model, micro_op_resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    Serial.println("AllocateTensors() failed");
    return;
  }

  // Get information about the memory area to use for the model's input.
  input = interpreter->input(0);
}

// The name of this function is important for Arduino compatibility.
void loop() {
  // Get image from provider
  TfLiteStatus status = GetImage(kNumCols, kNumRows, kNumChannels, input->data.int8);

  if (status != kTfLiteOk) {
    Serial.println("Image capture failed, skipping this frame.");
    vTaskDelay(50);
    return;
  }

  // Run inference on the captured image
  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Inference failed on this frame.");
    vTaskDelay(50);
    return;
  }

  TfLiteTensor* output = interpreter->output(0);

  // Get scores
  int8_t person_score = output->data.uint8[kPersonIndex];
  int8_t no_person_score = output->data.uint8[kNotAPersonIndex];

  float person_score_f = (person_score - output->params.zero_point) * output->params.scale;
  float no_person_score_f = (no_person_score - output->params.zero_point) * output->params.scale;

  // Respond to detection (LCD / Serial)
  RespondToDetection(person_score_f, no_person_score_f);
  vTaskDelay(100); // 100 ms delay to avoid watchdog

}




