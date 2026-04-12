#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../Capteurs/Temperature/TempSensor.h"
#include "../Capteurs/Lumiere/LightSensor.h"
#include "../Capteurs/Eau/WaterSensor.h"
#include "../Capteurs/Moisissure/MoistureSensor.h"
#include "../Capteurs/Gaz/gas_sensor.h"
#include "../Actionneurs/Relais/Relay.h"
#include "../Actionneurs/StepMoteur/StepMotor.h"
#include "../Actionneurs/ServoMoteur/Servo.h"
#include "nvs_flash.h"
#include "../Dashboard/Server.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "../Dashboard/log_buffer.h"
#include "../Dashboard/wifi.h"
#include "../Synchronisation/Queues.h"
#include "../Synchronisation/EventGroup.h"
#include "../Capteurs/Mouvement/Mouvement.h"
#include "../Capteurs/rfid/rfid.h"
#include "../Capteurs/rfid/rfid.h"

#define PIR_PIN 13
#define LED_PIN 2

void app_main(void)
{
    create_queues();
    start_queue_handlers();
    start_event_group_handler();
    xTaskCreate(&get_temperature, "get temperature", 2048, NULL, 5, NULL);
    gas_sensor_start();
    relay_init(GPIO_NUM_23);
    servo_init(GPIO_NUM_18);
    servo_init(GPIO_NUM_19);
    servo_init(GPIO_NUM_27);

    xTaskCreate(&water_monitor_task, "get water level", 4096, NULL, 5, NULL);
    servo_init(GPIO_NUM_21);

    relay_init(GPIO_NUM_25);
    xTaskCreate(&get_light_intensity, "get light intensity", 2048, NULL, 5, NULL);

    xTaskCreate(&rfid_task, "rfid task", 4096, NULL, 5, NULL);

    motion_init(PIR_PIN, LED_PIN);
    motion_start();
    showdata();
}

// void app_main(void)
// {

//     log_buffer_init();

//     create_queues();
//     start_queue_handlers();
//     start_event_group_handler();
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
//     {
//         nvs_flash_erase();
//         nvs_flash_init();
//     }
//     ESP_LOGI("MAIN", "Starting WiFi...");
//     wifi_init();

//     vTaskDelay(pdMS_TO_TICKS(5000)); // wait for IP
//     start_webserver();
//     relay_init(GPIO_NUM_23);
//     relay_init(GPIO_NUM_22);
//     relay_init(GPIO_NUM_25);
//     servo_init(GPIO_NUM_18);
//     servo_init(GPIO_NUM_19);
//     servo_init(GPIO_NUM_21);

//     xTaskCreate(&get_temperature, "get temperature", 2048, NULL, 5, NULL);
//     xTaskCreate(&get_light_intensity, "get light intensity", 2048, NULL, 5, NULL);
//     xTaskCreate(&get_moisture_level, "get moisture level", 4096, NULL, 5, NULL);
//     xTaskCreate(&water_monitor_task, "get water level", 4096, NULL, 5, NULL);
//     gas_sensor_start();
//     showdata();
// }

// #define PIR_PIN 13
// #define LED_PIN 2

// void app_main(void)
// {
//
// }