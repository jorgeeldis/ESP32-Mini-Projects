//! NOT WORKING
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints
// 7 segmentos debe ser anodo comun

#include <stdio.h>             // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs

#define BT 27 // Definiendo el pin (17) en donde boton accionara 

int display[] = {14, 34, 33, 25, 26, 12, 13}; // Los LEDs del 7 segmentos

void init_hw(void); // llamando la funcion de input y outputs

char matriz[10][7] = // Inicializando las variables y que leds encender para los numeros
    {
        {0, 0, 0, 0, 0, 0, 1}, // 0
        {1, 0, 0, 1, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0}, // 2
        {0, 0, 0, 0, 1, 1, 0}, // 3
        {1, 0, 0, 1, 1, 0, 0}, // 4
        {0, 1, 0, 0, 1, 0, 0}, // 5
        {0, 1, 0, 0, 0, 0, 0}, // 6
        {0, 0, 0, 1, 1, 1, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0}, // 8
        {0, 0, 0, 0, 1, 0, 0}, // 8
};

// Tiene que ir siempre para poder hacer funcionar los input y outputs
void init_hw(void)
{
    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_DEF_INPUT;
    io_conf.pin_bit_mask = (1ULL << BT); // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_ONLY;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);

    io_conf.mode = GPIO_MODE_DEF_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << display[0]) |
                           (1ULL << display[1]) |
                           (1ULL << display[2]) |
                           (1ULL << display[3]) |
                           (1ULL << display[4]) |
                           (1ULL << display[5]) |
                           (1ULL << display[6]); // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

// El código principal en donde se prenden LEDs
void app_main()
{

    init_hw(); // Llamando el I/O plugin

    int cnt = 0;                // Inicializando el counter
    for (int i = 0; i < 7; i++) // Hasta que i llegue a 7
    {
        gpio_set_level(display[i], matriz[0][i]); // Display sale 0
    }
    while (1)
    {
        int state_bt = gpio_get_level(BT); // Obtener estado de boton
        for (int i = 0; i < 7; i++)
        {
            gpio_set_level(display[i], matriz[cnt][i]); // Por cada presionar de boton se suma y sale nuevo num
        }

        cnt = (state_bt && cnt < 10) ? (cnt + 1) : cnt; // Sale el numero del boton menor a 10
        cnt = cnt < 9 ? 0 : cnt;

        vTaskDelay(pdMS_TO_TICKS(200)); // Delay anti rebote
    }
}