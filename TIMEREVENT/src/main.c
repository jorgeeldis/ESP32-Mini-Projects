//* FULLY WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs
#include "esp_log.h"           // Libreria para mandar mensajes dentro del codigo para verificar si se habilito algo
#include "freertos/timers.h"   // Libreria para usar funciones de timer

#define LED1 32                         // Definiendo el pin (2) en donde LED alumbrara
#define GPIO_LED_PIN_SEL (1ULL << LED1) // 1ULL es para definir una constante como unsigned (1)
int interval = 1000;                    // Los intervalos se usan para el LED que parpadee 1 segundo
int timerid = 1;                        // El id del timer para numerar
uint8_t led_level = 0;                  // El nivel del LED inicial (Apagado)

static const char *tag = "app_main"; // Puntero para el codigo principal
TimerHandle_t xTimers;

void init_led(void);   // Configuracion del I/O
void init_blink(void); // Creamos la funcion de los blinks
void set_timer(void);  // Creamos la funcion que cumple el "TaskDelay"

void vTimerCallBack(TimerHandle_t pxTimer)
{
    init_blink();
    ESP_LOGI(tag, "Evento llamado por el timer");
}

// Tiene que ir siempre para poder hacer funcionar los input y outputs
void init_led(void)
{
    gpio_config_t io_conf;
    io_conf.mode = GPIO_MODE_DEF_OUTPUT;
    io_conf.pin_bit_mask = GPIO_LED_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

void init_blink(void)
{
    led_level = !led_level;          // Led cambia su estado y ocupa ese estado nuevo
    gpio_set_level(LED1, led_level); // Se le agrega ese estado a el LED
}

// El código principal en donde se prenden LEDs
void app_main()
{
    init_led();  // Llamando la funcion para iniciar el I/O
    set_timer(); // Llamando la funcion en donde se usa el "TaskDelay"
}

void set_timer(void)
{
    ESP_LOGI(tag, "Inicializacion de la configuración del timer"); // Mensaje que sale en terminal
    xTimers = xTimerCreate("Timer",                                // Just a text name, not used by the kernel.
                           (pdMS_TO_TICKS(interval)),              // The timer period in ticks.
                           pdTRUE,                                 // The timers will auto-reload themselves when they expire.
                           (void *)timerid,                        // Assign each timer a unique id equal to its array index.
                           vTimerCallBack                          // Each timer calls the same callback when it expires.
    );
    if (xTimers == NULL)
    {                                         // The timer was not created.
        ESP_LOGI(tag, "Timer no fue creado"); // Mensaje que sale en terminal
    }
    else

    {
        if (xTimerStart(xTimers, 0) != pdPASS)
        {
            // The timer could not be set into the Active state.
            ESP_LOGI(tag, "El timer no se puede establecer en el estado activo"); // Mensaje que sale en terminal
        }
    }
}
