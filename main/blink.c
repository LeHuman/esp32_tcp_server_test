#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>

#define BLINK_GPIO CONFIG_BLINK_GPIO
static bool run_blink = false;
const TickType_t xDelay = portTICK_PERIOD_MS/3;

static void blink() {
    run_blink = true;
}

static void blink_task(void *pvParameters) {
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    for (;;) {
        if (run_blink) {
            gpio_set_level(BLINK_GPIO, 1);
            vTaskDelay(xDelay);
            gpio_set_level(BLINK_GPIO, 0);
            run_blink = false;
        }
        vTaskDelay(xDelay);
    }
    vTaskDelete(NULL);
}
