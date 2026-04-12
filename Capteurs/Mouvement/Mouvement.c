#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "Mouvement.h"

// Internal pins
static gpio_num_t pir_pin;
static gpio_num_t led_pin;

// ----------- INIT -----------
void motion_init(gpio_num_t pir, gpio_num_t led)
{
    pir_pin = pir;
    led_pin = led;

    // PIR config
    gpio_config_t pir_config = {
        .pin_bit_mask = (1ULL << pir_pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&pir_config);

    // LED config
    gpio_config_t led_config = {
        .pin_bit_mask = (1ULL << led_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&led_config);
}

// ----------- TASK -----------
static void motion_task(void *arg)
{
    int last_state = -1;

    while (1)
    {
        int motion = gpio_get_level(pir_pin);

        if (motion != last_state)
        {
            printf("PIR Value: %d\n", motion);

            if (motion)
            {
                printf("Motion detected!\n");
                gpio_set_level(led_pin, 1);
            }
            else
            {
                printf("No motion\n");
                gpio_set_level(led_pin, 0);
            }

            last_state = motion;
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ----------- START -----------
void motion_start(void)
{
    xTaskCreate(
        motion_task,
        "motion_task",
        2048,
        NULL,
        5,
        NULL);
}