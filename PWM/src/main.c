//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stddef.h>            // Libreria inicial para el codigo de C
#include "driver/ledc.h"       // Libreria para funciones de PWM para el LED
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs
#include "esp_log.h"           // Libreria para mandar mensajes en el monitor

#define LED 32 // Definiendo el pin (2) en donde LED alumbrara

static const char *tag = "main"; // a pointer to a constant char, meaning the char in question can't be modified
uint8_t led_level = 0;

void set_pwm(void);      // Llamando a la funcion de configuracion del PWM
void set_pwm_duty(void); // Llamando a la funcion que regula el ciclo de trabajo PWM

int dutyR = 0; // Ciclo de trabajo comienza en 0

void set_pwm(void) // Funcion de configuracion del PWM
{
    ledc_channel_config_t channelconfigR = {0};
    channelconfigR.gpio_num = 32;
    channelconfigR.speed_mode = LEDC_HIGH_SPEED_MODE;
    channelconfigR.channel = LEDC_CHANNEL_0;
    channelconfigR.intr_type = LEDC_INTR_DISABLE;
    channelconfigR.timer_sel = LEDC_TIMER_0;
    channelconfigR.duty = 0;

    ledc_channel_config(&channelconfigR);
    ESP_LOGE(tag, "Se configuro el PWM");

    ledc_timer_config_t timerconfig = {0};
    timerconfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    timerconfig.duty_resolution = LEDC_TIMER_8_BIT;
    // timerconfig.bit_num = LEDC_TIMER_10_BIT;
    timerconfig.timer_num = LEDC_TIMER_0;
    timerconfig.freq_hz = 1000;

    ledc_timer_config(&timerconfig);
}

void set_pwm_duty(void) // Funcion que regula el ciclo de trabajo PWM
{
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, dutyR);

    ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
}

// El código principal en donde se encuentra el LED pulsante (encendiendo y apagando)
void app_main()
{
    set_pwm(); // Llamando la función de configuracion

    while (1)
    {
        for (dutyR = 0; dutyR < 255; dutyR++) // Aumenta la intensidad del LED, contador incremental
        {
            set_pwm_duty();
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        for (dutyR = 255; dutyR > -1; dutyR--) // Disminuye la intensidad del LED, contador decremental
        {
            set_pwm_duty();
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
}