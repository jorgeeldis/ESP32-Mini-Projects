//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "driver/gpio.h"       // Libreria para funciones de PWM para el LED
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "esp_log.h"           // Libreria para mandar mensajes en el monitor

#define ledR 13             // Definiendo el pin (35) en donde LED alumbrara
#define ledG 14             // Definiendo el pin (35) en donde LED alumbrara
#define ledB 32             // Definiendo el pin (35) en donde LED alumbrara
#define STACK_SIZE 1024 * 2 // Definiendo el tamaño de ram que se usara
#define R_delay 1000        // Definiendo la duracion que se enciende el LED
#define G_delay 2000        // Definiendo la duracion que se enciende el LED
#define B_delay 4000        // Definiendo la duracion que se enciende el LED

static const char *tag = "app_main";
void init_led(void);             // Definiendo la funcion de la configuracion
void create_tasks(void);         // Definiendo la funcion de las tareas
void vTaskR(void *pvParameters); // creando tareas
void vTaskG(void *pvParameters); // creando tareas
void vTaskB(void *pvParameters); // creando tareas

// El código principal en donde se encuentra el LED pulsante (encendiendo y apagando)
void app_main()
{
    init_led(); // Llamando la función de configuracion
    create_tasks(); // llamando tareas

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("Hola desde main\n");
    }
}

void init_led(void) // configuracion
{
    gpio_reset_pin(ledR);
    gpio_set_direction(ledR, GPIO_MODE_OUTPUT);
    gpio_reset_pin(ledG);
    gpio_set_direction(ledG, GPIO_MODE_OUTPUT);
    gpio_reset_pin(ledB);
    gpio_set_direction(ledB, GPIO_MODE_OUTPUT);
}

void create_tasks(void) // creando tareas
{
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(vTaskR,
                "vTaskR",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);

    xTaskCreate(vTaskG,
                "vTaskG",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);

    xTaskCreate(vTaskB,
                "vTaskB",
                STACK_SIZE,
                &ucParameterToPass,
                1,
                &xHandle);
}

void vTaskR(void *pvParameters) // funcion de tareas
{
    while (1)
    {
        ESP_LOGI(tag, "Led R");
        gpio_set_level(ledR, 1);
        vTaskDelay(pdMS_TO_TICKS(R_delay));
        gpio_set_level(ledR, 0);
        vTaskDelay(pdMS_TO_TICKS(R_delay));
    }
}

void vTaskG(void *pvParameters) // funcion de tareas
{
    while (1)
    {
        ESP_LOGI(tag, "Led G");
        gpio_set_level(ledG, 1);
        vTaskDelay(pdMS_TO_TICKS(G_delay));
        gpio_set_level(ledG, 0);
        vTaskDelay(pdMS_TO_TICKS(G_delay));
    }
}

void vTaskB(void *pvParameters) // funcion de tareas
{
    while (1)
    {
        ESP_LOGI(tag, "Led B");
        gpio_set_level(ledB, 1);
        vTaskDelay(pdMS_TO_TICKS(B_delay));
        gpio_set_level(ledB, 0);
        vTaskDelay(pdMS_TO_TICKS(B_delay));
    }
}