//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "driver/ledc.h"       // Libreria para funciones de PWM para el LED
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/adc.h"        //
#include "esp_log.h"           // Libreria para mandar mensajes en el monitor

#define SAMPLE_CNT 32
static const adc1_channel_t adc_channel = ADC_CHANNEL_6;

#define LED_GPIO 32
static ledc_channel_config_t ledc_channel;

void init_hw(void) // Funcion de configuracion del PWM
{
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1000,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ledc_timer_config(&ledc_timer);

    ledc_channel.hpoint = 0;
    ledc_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel.channel = LEDC_CHANNEL_0;
    ledc_channel.gpio_num = LED_GPIO;
    ledc_channel.timer_sel = LEDC_TIMER_0;
    ledc_channel.duty = 0;

    ledc_channel_config(&ledc_channel);
}

// El código principal en donde se encuentra el LED pulsante (encendiendo y apagando)
void app_main()
{
    init_hw(); // Llamando la función de configuracion

    while (1)
    {
        uint32_t adc_val = 0;
        for (int i = 0; i < SAMPLE_CNT; i++)
        {
            adc_val += adc1_get_raw(adc_channel);
        }
        adc_val /= SAMPLE_CNT;

        ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, adc_val);

        ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);

        vTaskDelay(500/portTICK_RATE_MS);
    }
}