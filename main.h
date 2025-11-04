#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"

#include "esp_hidd_prf_api.h"
#include "esp_bt_defs.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_gatt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "driver/gpio.h"
#include "hid_dev.h"

#include "sdkconfig.h"
#include "driver/i2c_master.h"
#include <math.h>

#define I2C_MASTER_SCL_IO           8                           /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           10                          /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM              I2C_NUM_0                   /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ          40000                       /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS       1000

#define WHOAMI_REG_ADDR             0x75
#define I2C_ICM_ADDR                0x68
#define ACCEL_DATA_X1               0x0B
#define PWR_MGMTO                   0x1F
#define PWR_SLEEP                   0x00
#define PWR_WAKEUP                  0x03

#define A_LOT_UP                    40
#define A_BIT_UP                    10
#define A_LOT_DOWN                 -40
#define A_BIT_DOWN                 -10
#define A_LOT_RIGHT                 40
#define A_BIT_RIGHT                 10
#define A_LOT_LEFT                 -40
#define A_BIT_LEFT                 -10

#define HID_DEMO_TAG "HID_lab4_2"
#define CHAR_DECLARATION_SIZE   (sizeof(uint8_t))
#define HIDD_DEVICE_NAME            "lab4_2"

void hid_demo_task(void *pvParameters);
void app_main(void);
