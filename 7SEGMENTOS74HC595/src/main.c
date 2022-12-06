//! HAVENT TRIED
// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor serial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"       // Libreria para el driver de Input y Outputs

#define dataPin 15 // Pin conectado al DS de 74HC595 (pin 14)
#define latchPin 2 // Pin conectado al ST_CP de 74HC595 (pin 12)
#define clockPin 4 // Pin conectado al SH_CP de 74HC595 (pin 11)
#define DATAPIN_PIN_SEL (1ULL << dataPin)
#define LATCHPIN_PIN_SEL (1ULL << latchPin)
#define CLOCKPIN_PIN_SEL (1ULL << clockPin)
#define LSBFIRST 0

uint8_t num[] = {
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e}; // Los LEDs del 7 segmentos

void init_hw(void); // llamando la funcion de input y outputs
void desplaza(uint8_t pin_dato, uint8_t reloj, uint8_t ordenbit, uint8_t val);
void WriteData(int value);

// Tiene que ir siempre para poder hacer funcionar los input y outputs
static void init_hw(void)
{
    gpio_config_t io_conf;

    io_conf.mode = GPIO_MODE_DEF_OUTPUT;
    io_conf.pin_bit_mask = DATAPIN_PIN_SEL | LATCHPIN_PIN_SEL | CLOCKPIN_PIN_SEL; // Lo unico que se cambiaria
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&io_conf);
}

void desplaza(uint8_t pin_dato, uint8_t reloj, uint8_t ordenbit, uint8_t val) // Funcion para ir pasando los numeros por el 7 segmentos
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        if (ordenbit == LSBFIRST)
        {
            gpio_set_level(pin_dato, !!(val & (1 << i)));
        }
        else
        {
            gpio_set_level(pin_dato, !!(val & (1 << (7 - i))));
        }
        gpio_set_level(reloj, 1);
        gpio_set_level(reloj, 0);
    }
}

void WriteData(int value)
{
    // Hacer que la salida de latchPin sea de bajo nivel
    gpio_set_level(latchPin, 0);
    // Enviar datos a 74HC595
    desplaza(dataPin, clockPin, 0, value);
    // Hacer la salida de latchPin alto nivel, luego el IC actualizara datos en la salida paralela
    gpio_set_level(latchPin, 1);
}

// El código principal en donde se prenden LEDs
void app_main()
{

    init_hw(); // Llamando el I/O plugin

    while (1)
    {
        // Mostrar 0-F en Display
        for (int i = 0; i < 16; i++)
        {
            WriteData(num[i]);               // Send Data to 74HC595
            vTaskDelay(pdMS_TO_TICKS(1000)); // Cada 1 segundo mostrar
            WriteData(0xff);                 // Clear 7 Segments
        }
    }
}