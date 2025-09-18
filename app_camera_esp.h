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

#ifndef TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
#define TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_

#include "sensor.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_main.h"

/**
 * PIXFORMAT_RGB565    // 2BPP/RGB565
 * PIXFORMAT_YUV422    // 2BPP/YUV422
 * PIXFORMAT_GRAYSCALE // 1BPP/GRAYSCALE
 * PIXFORMAT_JPEG      // JPEG/COMPRESSED
 * PIXFORMAT_RGB888    // 3BPP/RGB888
 */
#define CAMERA_PIXEL_FORMAT PIXFORMAT_RGB565    // 2BPP/RGB565

/*
 * FRAMESIZE_96X96    // 96x96
 * FRAMESIZE_QQVGA    // 160x120
 * FRAMESIZE_QCIF     // 176x144
 * FRAMESIZE_HQVGA    // 240x176
 * FRAMESIZE_QVGA     // 320x240
 
 * FRAMESIZE_CIF      // 400x296
 * FRAMESIZE_VGA      // 640x480
 */
#define CAMERA_FRAME_SIZE FRAMESIZE_QQVGA    // 160x120

// ================= CAMERA MODEL MANUAL SELECTION =================
// Uncomment ONLY one camera model before compiling:

//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE  // Has PSRAM
//#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
//#define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
//#define CAMERA_MODEL_M5STACK_CAMS3_UNIT  // Has PSRAM
//#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
//#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM

// ** Espressif Internal Boards **
#define CAMERA_MODEL_FREENOVE_ESP32S3_CAM // Has PSRAM
//#define CAMERA_MODEL_ESP32_CAM_BOARD
//#define CAMERA_MODEL_ESP32S2_CAM_BOARD
//#define CAMERA_MODEL_ESP32S3_CAM_LCD
//#define CAMERA_MODEL_DFRobot_FireBeetle2_ESP32S3 // Has PSRAM
//#define CAMERA_MODEL_DFRobot_Romeo_ESP32S3 // Has PSRAM

#if defined(CAMERA_MODEL_WROVER_KIT)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  21
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27

#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    19
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    5
#define Y2_GPIO_NUM    4
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

#elif defined(CAMERA_MODEL_ESP_EYE)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  4
#define SIOD_GPIO_NUM  18
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    36
#define Y8_GPIO_NUM    37
#define Y7_GPIO_NUM    38
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    35
#define Y4_GPIO_NUM    14
#define Y3_GPIO_NUM    13
#define Y2_GPIO_NUM    34
#define VSYNC_GPIO_NUM 5
#define HREF_GPIO_NUM  27
#define PCLK_GPIO_NUM  25

#define LED_GPIO_NUM 22

#elif defined(CAMERA_MODEL_M5STACK_PSRAM)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  25
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    32
#define VSYNC_GPIO_NUM 22
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#elif defined(CAMERA_MODEL_M5STACK_V2_PSRAM)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  22
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    32
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#elif defined(CAMERA_MODEL_M5STACK_WIDE)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  22
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    32
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#define LED_GPIO_NUM 2

#elif defined(CAMERA_MODEL_M5STACK_ESP32CAM)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  25
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    17
#define VSYNC_GPIO_NUM 22
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#elif defined(CAMERA_MODEL_M5STACK_UNITCAM)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  25
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    32
#define VSYNC_GPIO_NUM 22
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#elif defined(CAMERA_MODEL_M5STACK_CAMS3_UNIT)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM 21
#define XCLK_GPIO_NUM  11
#define SIOD_GPIO_NUM  17
#define SIOC_GPIO_NUM  41

#define Y9_GPIO_NUM    13
#define Y8_GPIO_NUM    4
#define Y7_GPIO_NUM    10
#define Y6_GPIO_NUM    5
#define Y5_GPIO_NUM    7
#define Y4_GPIO_NUM    16
#define Y3_GPIO_NUM    15
#define Y2_GPIO_NUM    6
#define VSYNC_GPIO_NUM 42
#define HREF_GPIO_NUM  18
#define PCLK_GPIO_NUM  12

#define LED_GPIO_NUM 14

#elif defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM  32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  0
#define SIOD_GPIO_NUM  26
#define SIOC_GPIO_NUM  27

#define Y9_GPIO_NUM    35
#define Y8_GPIO_NUM    34
#define Y7_GPIO_NUM    39
#define Y6_GPIO_NUM    36
#define Y5_GPIO_NUM    21
#define Y4_GPIO_NUM    19
#define Y3_GPIO_NUM    18
#define Y2_GPIO_NUM    5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM  23
#define PCLK_GPIO_NUM  22

// 4 for flash led or 33 for normal led
#define LED_GPIO_NUM   4

#elif defined(CAMERA_MODEL_TTGO_T_JOURNAL)
#define PWDN_GPIO_NUM  0
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM  27
#define SIOD_GPIO_NUM  25
#define SIOC_GPIO_NUM  23

#define Y9_GPIO_NUM    19
#define Y8_GPIO_NUM    36
#define Y7_GPIO_NUM    18
#define Y6_GPIO_NUM    39
#define Y5_GPIO_NUM    5
#define Y4_GPIO_NUM    34
#define Y3_GPIO_NUM    35
#define Y2_GPIO_NUM    17
#define VSYNC_GPIO_NUM 22
#define HREF_GPIO_NUM  26
#define PCLK_GPIO_NUM  21

#elif defined(CAMERA_MODEL_XIAO_ESP32S3)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39

#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    11
#define Y7_GPIO_NUM    12
#define Y6_GPIO_NUM    14
#define Y5_GPIO_NUM    16
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    17
#define Y2_GPIO_NUM    15
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

#elif defined(CAMERA_MODEL_ESP32_CAM_BOARD)
// The 18 pin header on the board has Y5 and Y3 swapped
#define USE_BOARD_HEADER 0
#define PWDN_GPIO_NUM    32
#define RESET_GPIO_NUM   33
#define XCLK_GPIO_NUM    4
#define SIOD_GPIO_NUM    18
#define SIOC_GPIO_NUM    23

#define Y9_GPIO_NUM 36
#define Y8_GPIO_NUM 19
#define Y7_GPIO_NUM 21
#define Y6_GPIO_NUM 39
#if USE_BOARD_HEADER
#define Y5_GPIO_NUM 13
#else
#define Y5_GPIO_NUM 35
#endif
#define Y4_GPIO_NUM 14
#if USE_BOARD_HEADER
#define Y3_GPIO_NUM 35
#else
#define Y3_GPIO_NUM 13
#endif
#define Y2_GPIO_NUM    34
#define VSYNC_GPIO_NUM 5
#define HREF_GPIO_NUM  27
#define PCLK_GPIO_NUM  25

#elif defined(CAMERA_MODEL_ESP32S3_CAM_LCD)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  40
#define SIOD_GPIO_NUM  17
#define SIOC_GPIO_NUM  18

#define Y9_GPIO_NUM    39
#define Y8_GPIO_NUM    41
#define Y7_GPIO_NUM    42
#define Y6_GPIO_NUM    12
#define Y5_GPIO_NUM    3
#define Y4_GPIO_NUM    14
#define Y3_GPIO_NUM    47
#define Y2_GPIO_NUM    13
#define VSYNC_GPIO_NUM 21
#define HREF_GPIO_NUM  38
#define PCLK_GPIO_NUM  11

#elif defined(CAMERA_MODEL_ESP32S2_CAM_BOARD)
// The 18 pin header on the board has Y5 and Y3 swapped
#define USE_BOARD_HEADER 0
#define PWDN_GPIO_NUM    1
#define RESET_GPIO_NUM   2
#define XCLK_GPIO_NUM    42
#define SIOD_GPIO_NUM    41
#define SIOC_GPIO_NUM    18

#define Y9_GPIO_NUM 16
#define Y8_GPIO_NUM 39
#define Y7_GPIO_NUM 40
#define Y6_GPIO_NUM 15
#if USE_BOARD_HEADER
#define Y5_GPIO_NUM 12
#else
#define Y5_GPIO_NUM 13
#endif
#define Y4_GPIO_NUM 5
#if USE_BOARD_HEADER
#define Y3_GPIO_NUM 13
#else
#define Y3_GPIO_NUM 12
#endif
#define Y2_GPIO_NUM    14
#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  4
#define PCLK_GPIO_NUM  3

#elif defined(CAMERA_MODEL_ESP32S3_EYE) || defined(CAMERA_MODEL_FREENOVE_ESP32S3_CAM)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  15
#define SIOD_GPIO_NUM  4
#define SIOC_GPIO_NUM  5

#define Y2_GPIO_NUM 11
#define Y3_GPIO_NUM 9
#define Y4_GPIO_NUM 8
#define Y5_GPIO_NUM 10
#define Y6_GPIO_NUM 12
#define Y7_GPIO_NUM 18
#define Y8_GPIO_NUM 17
#define Y9_GPIO_NUM 16

#define VSYNC_GPIO_NUM 6
#define HREF_GPIO_NUM 7
#define PCLK_GPIO_NUM 13

#elif defined(CAMERA_MODEL_DFRobot_FireBeetle2_ESP32S3) || defined(CAMERA_MODEL_DFRobot_Romeo_ESP32S3)
#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  45
#define SIOD_GPIO_NUM  1
#define SIOC_GPIO_NUM  2

#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    46
#define Y7_GPIO_NUM    8
#define Y6_GPIO_NUM    7
#define Y5_GPIO_NUM    4
#define Y4_GPIO_NUM    41
#define Y3_GPIO_NUM    40
#define Y2_GPIO_NUM    39
#define VSYNC_GPIO_NUM 6
#define HREF_GPIO_NUM  42
#define PCLK_GPIO_NUM  5

#else
#error "Camera model not selected"
#endif

#ifdef __cplusplus
extern "C" {
#endif

int app_camera_init();

#ifdef __cplusplus
}
#endif

#endif  // TENSORFLOW_LITE_MICRO_EXAMPLES_PERSON_DETECTION_ESP_APP_CAMERA_ESP_H_
