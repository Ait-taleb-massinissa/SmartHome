#ifndef MOTION_H
#define MOTION_H

#include "driver/gpio.h"

// Initialize motion system (PIR + LED)
void motion_init(gpio_num_t pir_pin, gpio_num_t led_pin);

// Start FreeRTOS task
void motion_start(void);

#endif