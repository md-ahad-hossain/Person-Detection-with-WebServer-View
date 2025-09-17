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

#include <Arduino.h>
#include "app_camera_esp.h"
#include "esp_camera.h"
#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "app_camera_esp";

/**
 * Initialize FREENOVE ESP32S3 Camera
 * RGB565 format (color video), QVGA (320x240)
 */
int app_camera_init() {

    camera_config_t config;

    // LEDC settings (XCLK)
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    // Camera pin mapping (FREENOVE ESP32S3 CAM)
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    // Camera settings
    config.xclk_freq_hz = 20000000;                // 20 MHz XCLK
    config.pixel_format = CAMERA_PIXEL_FORMAT,     // app_camera_esp.h থেকে Setect করতে হবে
    config.frame_size   = CAMERA_FRAME_SIZE,      // app_camera_esp.h থেকে Setect করতে হবে
    config.jpeg_quality = 12;                   // only used for JPEG
    config.fb_count     = 1;                   // double buffer
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM; // store in PSRAM if available

    // camera init

    printf("Free heap before camera init: %d\n", esp_get_free_heap_size()); // init আগে মেমোরি দেখা যাবে

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
      printf("Camera init failed with error 0x%X\n", err);
      return -1;
    }

    printf("Free heap after camera init: %d bytes\n", esp_get_free_heap_size()); // init পরে মেমোরি দেখা যাবে 

    // Sensor adjustments
    sensor_t *s = esp_camera_sensor_get();
    if (s) {
        s->set_vflip(s, 1);
        s->set_brightness(s, 1);
        s->set_saturation(s, -2);
        s->set_framesize(s, CAMERA_FRAME_SIZE);
    }

    printf("Camera initialized successfully!\n");
    return 0;
}

