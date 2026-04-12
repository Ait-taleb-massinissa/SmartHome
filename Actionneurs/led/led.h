#ifndef LED_H
#define LED_H

#include "driver/gpio.h"

void led_init(gpio_num_t pin);
void led_on(void);
void led_off(void);
void led_set(int state);

#endif