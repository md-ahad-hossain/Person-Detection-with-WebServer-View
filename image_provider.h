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

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_IMAGE_PROVIDER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_IMAGE_PROVIDER_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "esp_timer.h"

#include "app_camera_esp.h"
#include "esp_camera.h"
#include "model_settings.h"
#include "esp_main.h"

#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_log.h"

// Camera initialization function
inline TfLiteStatus InitCamera() {
    int ret = app_camera_init(); // low-level init
    return (ret == 0) ? kTfLiteOk : kTfLiteError;
}

// Function to capture image and convert RGB565 -> grayscale
inline TfLiteStatus GetImage(int image_width, int image_height, int channels, int8_t* image_data) {
    camera_fb_t* fb = esp_camera_fb_get();
    if (!fb) return kTfLiteError;

    int rows = (fb->height < kNumRows) ? fb->height : kNumRows;
    int cols = (fb->width  < kNumCols) ? fb->width  : kNumCols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uint16_t pixel = ((uint16_t*)fb->buf)[i * fb->width + j];

            uint8_t hb = pixel & 0xFF;
            uint8_t lb = pixel >> 8;
            uint8_t r = (lb & 0x1F) << 3;
            uint8_t g = ((hb & 0x07) << 5) | ((lb & 0xE0) >> 3);
            uint8_t b = (hb & 0xF8);

            int8_t grey = ((305 * r + 600 * g + 119 * b) >> 10) - 128;
            image_data[i * kNumCols + j] = grey;
        }
    }

    esp_camera_fb_return(fb);
    return kTfLiteOk;
}

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_IMAGE_PROVIDER_H_
