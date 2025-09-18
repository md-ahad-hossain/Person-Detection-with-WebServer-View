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

extern volatile bool g_person_detected;

#define ALARM_PIN 2   // Alarm GPIO পিন

// Called every time the results of a person detection run are available.
// person_score: confidence that a person is present (0.0 - 1.0)
// no_person_score: confidence that no person is present (0.0 - 1.0)
// ফাংশন declarations
void RespondToDetection(float person_score, float no_person_score);
void handleDetection(float person_score, float no_person_score);

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_DETECTION_RESPONDER_H_


