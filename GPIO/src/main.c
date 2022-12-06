//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs

#define LED1 32                  // Definiendo el pin (2) en donde LED alumbrara
#define LED1_SEL (1ULL << LED1) // 1ULL es para definir una constante como unsigned (1)

// Tiene que ir siempre para poder hacer funcionar los input y outputs
static void init_hw(void)
{
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_DEF_OUTPUT;
    io_conf.pin_bit_mask = LED1_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

// El código principal en donde se prende LED un segundo y se apaga
void app_main()
{

    init_hw(); // Llamando el I/O plugin

    // Siempre se repite porque 1 es siempre verdad
    while (1)
    {
        gpio_set_level(LED1, 1);         // Encendiendo LED
        printf("Led Encendido \n");      // Imprimiendo en el monitor serial
        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperando 1 segundo
        gpio_set_level(LED1, 0);         // Apagando LED
        printf("Led Apagado \n");        // Imprimiendo en el monitor serial
        vTaskDelay(pdMS_TO_TICKS(1000)); // Esperando 1 segundo
    }
}