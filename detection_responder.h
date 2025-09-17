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

// Provides an interface to take an action based on the output from the person
// detection model.

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_DETECTION_RESPONDER_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_DETECTION_RESPONDER_H_

#include <Arduino.h>
#include "tensorflow/lite/c/common.h"
#include "image_provider.h"
#include "esp_main.h"
#include "esp_log.h"

#define ALARM_PIN 2   // Alarm GPIO পিন

// GPIO পিন ইনিশিয়ালাইজ
inline void setupAlarmPin() {
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(ALARM_PIN, LOW);
}

inline void RespondToDetection(float person_score, float no_person_score) {
    bool person_detected = (person_score >= 0.6f); // Threshold 60%

    // GPIO Alarm trigger
    digitalWrite(ALARM_PIN, person_detected ? HIGH : LOW);

    ESP_LOGI(TAG, "Person score: %.2f, Detected: %s", person_score, person_detected ? "YES" : "NO");
}

// মূল ডিটেকশন লুপ বা ফ্রেম প্রক্রিয়াকরণে কল করবে
inline void handleDetection(float person_score, float no_person_score) {
    RespondToDetection(person_score, no_person_score);
}

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_DETECTION_RESPONDER_H_

