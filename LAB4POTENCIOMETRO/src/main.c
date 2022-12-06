//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/dac.h"        // Libreria para conversion digital analoga
#include "driver/dac_common.h" // Libreria para conversion digital analoga
#include "driver/adc.h"        // Libreria para conversion analoga digital
#include "esp_log.h"           // Libreria para mandar mensajes en el monitor

#define SAMPLE_CNT 34
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;

#define LED_GPIO 25
static const dac_channel_t dac_channel = DAC_CHANNEL_1;

void init_hw(void) // Funcion de configuracion del PWM
{
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
    dac_output_enable(dac_channel);
}

// El código principal en donde se encuentra el LED pulsante (encendiendo y apagando)
void app_main()
{
    init_hw(); // Llamando la función de configuracion

    uint32_t adc_val = 0;
    float analogvoltage;
    uint32_t dac_val = 0;

    while (1)
    {

        for (int i = 0; i < SAMPLE_CNT; i++)
        {
            adc_val += adc1_get_raw(adc_channel);
        }
        adc_val /= SAMPLE_CNT;

        vTaskDelay(500 / portTICK_RATE_MS);

        analogvoltage = (adc_val * 3.3) / 1024;
        dac_val = (analogvoltage * 248) / 3.3;

        dac_output_voltage(dac_channel, dac_val);

        printf("adc val: %9d | voltage: %9f | dac val: %9d\n", adc_val, analogvoltage, dac_val);
    }
}