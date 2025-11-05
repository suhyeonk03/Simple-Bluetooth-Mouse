# Simple-Bluetooth-Mouse
## Project Overview
A simple Bluetooth mouse that uses the ESP32’s built-in ICM-42670-P sensor for inclination-based movement and performs a periodic left-click every 2 seconds

<p align="center">
  <img src="Arduino_Orange" alt="LCD and ESP board" width="600" height="500">
</p>
<p align="center">
  <img src="Jupyter_Orange" alt="LCD and ESP board" width="600" height="500">
</p>

## Used Libraries
## Hardware
- ESP32 robust board
- 

## Phase 1: Board movement
For this lab, I used the ICM_42670_p sensor to print UP/DOWN or LEFT/RIGHT through
ESP_LOGI based on the ESP board’s inclination
I could implement this function by modifying the provided i2c example code and changing some
addresses (such as who_am_i, ICM, accel_data, pwr, etc.) according to the ICM_42670_P
datasheet. Also, I used ChatGPT to help convert the signed 16-bit integer values into a unit
(gram) that I can actually use to determine the direction of the board’s inclination.
I didn’t encounter any major difficulties while completing this part, as it mainly involved
connecting a new type of peripheral to the i2c, which we were already familiar with from lab2
and lab3.

## Phase 2: Move the mouse from left to right
This part required using the provided ble_hid_device_demo repository to implement the
Bluetooth functionality that moves the mouse left and right on the screen, then pauses for five
seconds.
To complete this part, I slightly modified the hid_demo_task function. I used the provided
esp_hidd_send_mouse_value function with hid_conn_id, 0x00 for the button, <x> for the
x-direction, and 0 for the y-direction.
At first, I was a bit confused about how to implement a function to control my laptop’s mouse.
However, after spending a few minutes reading through the files in the ble_hid_device_demo
repository, I found the esp_hidd_send_mouse_value function, which simply required providing
an x-pixel value to move the mouse in the desired direction

## Phase 3: Integration
This part combines the previous tasks. The mouse movement depends on the ESP board’s
inclination and performs a left-click approximately every two seconds.
I removed the char dir[] array, which originally stored UP/DOWN or LEFT/RIGHT values for
printing with ESP_LOGI. Instead, I used variables dx and dy to store values such as macros:
A_LOT_<UP/DOWN/LEFT/RIGHT> or A_BIT_<UP/DOWN/LEFT/RIGHT>, allowing me to use
them as arguments for the esp_hidd_send_mouse_value function. In addition, I implemented
code to perform a left-click roughly every two seconds.
I didn’t encounter any major issues while completing this part—only minor errors such as
undeclared variables.

## Credentials
- DFRobot_RGBLCD1602.cpp and DFRobot_RGBLCD1602.h are by 2010 DFRobot Co.Ltd
- main.cpp is by 2024 Espressif Systems (Shanghai) CO LTD, espressif/esp-idf/examples/peripherals/i2c/i2c_basic/main


## Used Libraries
- <stdio.h>
- <string.h>
- <math.h>
- "freertos/FreeRTOS.h"
- "freertos/task.h"
- "driver/i2c.h"
- "DFRobot_RGBLCD1602.h"
- "esp_log.h"
- "esp_system.h"

## Hardware
- ESP32-C3-DevKit-RUST-1
- DFRobot_RGBLCD1602
- Breadboard, wires, female header pins, and male header pins

## Phase 1: Soldering
Soldered female header pins onto the ESP32 board using an AOYUE 9378 soldering station.

## Phase 2: Temperature and Humidity read
Connects to the SHTC3 sensor at i2c address 0x70 and controls its power using the wake-up command (0x3517) and the sleep command (0xB098). The read_from_SHT3_temp and read_from_SHT3_humi functions each read 3 bytes using the i2c_master_write_to_device and i2c_master_read_from_device functions. After verifying data validity through a checksum and converting the 16-bit values into readable numbers, the program outputs the temperature in Celsius and humidity as a percentage.

## Phase 3: Display result on LCD (detailed expl, what act code does)
Modified the Arduino-based functions in DFRobot_RGBLCD1602.cpp to support the ESP32 interface. Then, initialized the LCD in main.cpp with a black backlight and set the cursor to position (0, 0). The LCD displays the current temperature and humidity obtained from Phase 2 in the format: "Temp:%dC,Hum:%d%%".

## Credits
- DFRobot_RGBLCD1602.cpp and DFRobot_RGBLCD1602.h — © 2010 DFRobot Co., Ltd.
- main.cpp structure — © 2024 Espressif Systems (Shanghai) Co., Ltd.
(Adapted from espressif/esp-idf/examples/peripherals/i2c/i2c_basic/main) 

