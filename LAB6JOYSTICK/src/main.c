//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor gserial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/dac.h"        // Libreria para conversion digital analoga
#include "driver/dac_common.h" // Libreria para conversion digital analoga
#include "driver/adc.h"        // Libreria para conversion analoga digital
#include "esp_log.h"           // Libreria para mandar mensajes en el monitor

#define BT 14
#define GPIO_BT_PIN_SEL (1ULL << BT)

#define SAMPLE_VRX 32
static const adc_channel_t adc_channel = ADC_CHANNEL_6;

#define SAMPLE_VRY 32
static const adc_channel_t adc_channelY = ADC_CHANNEL_7;

float VoltageX = 0.0;
float VoltageY = 0.0;
int DACX = 0;
int DACY = 0;

void init_hw(void)
{
    gpio_config_t io_config;

    io_config.mode = GPIO_MODE_INPUT;
    io_config.pin_bit_mask = GPIO_BT_PIN_SEL;
    io_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_config.pull_up_en = GPIO_PULLUP_ENABLE;
    io_config.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_config);
}

static void init_hwADC(void)
{
    adc1_config_width(ADC_WIDTH_BIT_10);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
    adc1_config_channel_atten(adc_channelY, ADC_ATTEN_DB_11);
    dac_output_enable(DAC_CHANNEL_1);
}

// El código principal en donde se encuentra el LED pulsante (encendiendo y apagando)
void app_main()
{
    init_hw();

    init_hwADC();

    while (1)
    {
        uint32_t adcX_val = 0;
        uint32_t adcY_val = 0;
    
        for (int i = 0; i < SAMPLE_VRX; i++)
        {
            adcX_val += adc1_get_raw(adc_channel);
        }

        for (int i = 0; i < SAMPLE_VRY; i++)
        {
            adcY_val += adc1_get_raw(adc_channelY);
        }

        adcX_val /= SAMPLE_VRX;
        adcY_val /= SAMPLE_VRY;
        int state_bt = gpio_get_level(BT);
        VoltageX = (adcX_val * 3.3) / 1024;
        DACX = (VoltageX * 255) / (3.3);
        VoltageY = (adcY_val * 3.3) / 1024;
        DACY = (VoltageY * 255) / (3.3);

        dac_output_voltage(DAC_CHANNEL_1, DACX);
        dac_output_voltage(DAC_CHANNEL_1, DACY);

        printf("VoltajeX= %.9F \t adcX_val= %d \t DACX= %d" "VoltajeY= %.9F \t adcY_val= %d \t DACY= %d state_bt= %d \t \n",
               VoltageX, adcX_val, DACX, VoltageY, adcY_val, DACY, state_bt);

        vTaskDelay(50 / portTICK_RATE_MS);
    }
}