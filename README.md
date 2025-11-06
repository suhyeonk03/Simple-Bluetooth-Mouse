# Simple-Bluetooth-Mouse
## Project Overview
A simple Bluetooth mouse that uses the ESP32’s built-in ICM-42670-P sensor for inclination-based movement and performs a periodic left-click every 2 seconds

## Used Libraries
- <stdio.h>
- <string.h>
- <stdlib.h>
- <stdint.h>
- <stdbool.h>
- <math.h>
- "freertos/FreeRTOS.h"
- "freertos/task.h"
- "freertos/event_groups.h"
- "driver/i2c_master.h"
- "esp_log.h"
- "esp_system.h"
- "esp_event.h"
- "nvs_flash.h"
- "esp_hidd_prf_api.h"
- "hidd_le_prf_int.h"
- "hid_dev.h"
- "main.h"
- "esp_bt.h"
- "esp_bt_main.h"
- "esp_bt_defs.h"
- "esp_bt_device.h"
- "esp_gap_ble_api.h"
- "esp_gatts_api.h"
- "esp_gatt_defs.h"
- "driver/gpio.h"

## Hardware
- ESP32-C3-DevKit-RUST-1

## Phase 1: Board movement
Connected to the ICM_42670_P built-in sensor via the I2C interface at address 0x68. Controlled the sensor’s power (0x1F) using the wake-up command (0x03) and the sleep command (0x00) to conserve energy when not reading data. Retrieved x, y, and z acceleration data using the i2c_master functions from registers starting at ACCEL_DATA_X1 (0x0B) through ACCEL_DATA_Z0 (0x10), reading a total of 6 bytes to determine the board’s inclination. Performed mathematical calculations to convert each 16-bit signed integer into degrees. Based on the inclination angle, the mouse movement speed varies (e.g., if x > 60° → Fast; else if x > 15° → Slow).

## Phase 2: Mouse movement
Modified the hid_demo_task function to integrate the Phase 1 code and the esp_hidd_send_mouse_value function, which controls the mouse of a connected Bluetooth device (e.g., laptop) by passing arguments such as hid_conn_id, left-click condition, dx, and dy. The function also performs a left-click approximately every 2 seconds, enabling it to perform basic actions such as opening or closing a tab.

## Credits
Code files - © 2024 Espressif Systems (Shanghai) Co., Ltd.
(Adapted from espressif/esp-idf/examples/bluetooth/bluedroid/ble/ble_hid_device_demo)
