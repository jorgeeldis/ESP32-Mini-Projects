//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stddef.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs

#define LED1 32                          // Definiendo el pin (35) en donde LED alumbrara
#define LED2 14                          // Definiendo el pin (35) en donde LED alumbrara
#define BT 27                            // Definiendo el pin (33) en donde Boton accionara
#define GPIO_LED1_PIN_SEL (1ULL << LED1) // 1ULL es para definir una constante como unsigned (1)
#define GPIO_LED2_PIN_SEL (1ULL << LED2) // 1ULL es para definir una constante como unsigned (1)
#define GPIO_BT_PIN_SEL (1ULL << BT)     // 1ULL es para definir una constante como unsigned (1)
#define ESP_INTR_FLAG_DEFAULT 0

static void button_handler(void *arg);

// Tiene que ir siempre para poder hacer funcionar los input y outputs
static void init_hw(void)
{
    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED1_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED2_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BT_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_up_en = 1;                 // Configurando la resistencia pull up del boton
    io_conf.intr_type = GPIO_INTR_NEGEDGE;

    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT); // Interrupciones, a single global ISR is registered for all GPIOS
    gpio_isr_handler_add(BT, button_handler, NULL);  // Instalar the drivers GPIO ISR handler service
}

static TickType_t next = 0; // Ticks como si fueran ms
// static bool led_state = false; // Estado inicial del LED
int counter = 0; // Counter para ir pasando de instruccion

static void IRAM_ATTR button_handler(void *arg) // Forces code into IRAM instead of flash, para almacenar data
{
    TickType_t now = xTaskGetTickCountFromISR(); // Obtener la cuenta de ticks del ISR
    if (now < next)                              // Si el anti rebote ya esta estable
    {
        return;
    }

    if (counter == 0)
    {
        // led_state = !led_state;                // Cambia el estado de LED
        gpio_set_level(LED1, 1);               // Da el estado al LED
        gpio_set_level(LED2, 0);               // Da el estado al LED
        next = now + 100 / portTICK_PERIOD_MS; // Anti rebote
        counter += 1;
        return; // Salir de funcion para volver a comparar
    }

    if (counter == 1)
    {
        gpio_set_level(LED1, 0);               // Da el estado al LED
        gpio_set_level(LED2, 1);               // Da el estado al LED
        next = now + 100 / portTICK_PERIOD_MS; // Anti rebote
        counter += 1;
        return; // Salir de funcion para volver a comparar
    }

    if (counter > 1)
    {
        gpio_set_level(LED1, 0);               // Da el estado al LED
        gpio_set_level(LED2, 0);               // Da el estado al LED
        next = now + 100 / portTICK_PERIOD_MS; // Anti rebote
        counter = 0;
        return; // Salir de funcion para volver a comparar
    }
}

// El código principal en donde se encienden los leds
void app_main()
{

    init_hw(); // Llamando el I/O plugin

    vTaskSuspend(NULL); // Handle to the task being suspended. Passing a NULL handle will cause the calling task to be suspended
}