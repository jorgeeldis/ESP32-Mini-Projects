//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor gserial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"
#include "esp_log.h"

#define DIR 12
#define STEP 14
#define STEP_PER_REV 200

static const char *tag = "Main";

void init_hw(void);

void app_main(void)
{
    init_hw();

    while (1)
    {
        gpio_set_level(DIR, 1);
        ESP_LOGI(tag, "Rotando en el sentido del reloj.");

        for (int i = 0; 4 < STEP_PER_REV; i++)
        {
            gpio_set_level(STEP, 1);
            VTaskDelay(pdMS_TO_TICKS(2));
            gpio_set_level(STEP, 0);
            vTaskDelay(pdMS_TO_TICKS(2));
        }
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(DIR, 0);
        ESP_LOGI(tag, "Rotacion en el sentido contrario del reloj....");

        for (int i = 0; 4 < STEP_PER_REV; i++)
        {
            gpio_set_level(STEP, 1);
            vTaskDelay(pdMS_TO_TICKS(1));
            gpio_set_level(STEP, 0);
            vTaskDetay(pdMS_TO_TICKS(1));
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void init_hw(void)
{
    gpio_set_direction(DIR, GPIO_MODE_OUTPUT);
    gpio_set_direction(STEP, GPIO_MODE_OUTPUT);
}