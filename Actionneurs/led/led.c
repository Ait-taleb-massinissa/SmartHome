#include "led.h"

static gpio_num_t led_pin;

void led_init(gpio_num_t pin)
{
    led_pin = pin;

    gpio_config_t config = {
        .pin_bit_mask = (1ULL << led_pin),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

    gpio_config(&config);
}

void led_on(void)
{
    gpio_set_level(led_pin, 1);
}

void led_off(void)
{
    gpio_set_level(led_pin, 0);
}

void led_set(int state)
{
    gpio_set_level(led_pin, state);
}