//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stddef.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs

#define LED 32                           // Definiendo el pin (12) en donde LED alumbrara
#define LED1 14                          // Definiendo el pin (14) en donde LED alumbrara
#define BT 27                            // Definiendo el pin (27) en donde boton accionara
#define GPIO_LED_PIN_SEL (1ULL << LED)   // 1ULL es para definir una constante como unsigned (1)
#define GPIO_LED1_PIN_SEL (1ULL << LED1) // 1ULL es para definir una constante como unsigned (1)
#define GPIO_BT_PIN_SEL (1ULL << BT)     // 1ULL es para definir una constante como unsigned (1)

// Tiene que ir siempre para poder hacer funcionar los input y outputs
static void init_hw(void)
{
    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED1_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BT_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = 1; // Usando el pull up interno para hacer funcionar el boton
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
        int state_bt = gpio_get_level(BT); // Leer si el boton esta en 0 o 1
        printf("%d\n", state_bt);          // Imprimiendo el estado del boton
        if (!state_bt)                     // Si el boton es diferente a 1
        {
            gpio_set_level(LED, 0);  // Colocar boton en 0 (apagado)
            gpio_set_level(LED1, 1); // Colocar boton en 1 (encendido)
        }
        else
        {
            gpio_set_level(LED, 1);  // Colocar boton en 1 (encendido)
            gpio_set_level(LED1, 0); // Colocar boton en 0 (apagado)
        }

        vTaskDelay(pdMS_TO_TICKS(200)); // Si no se pone, el micro va a ver eso como bucle infinito
        // vTaskDelay(NULL); // Mata la tarea, deja de contar el sistema, suspende y luego activa
    }
}