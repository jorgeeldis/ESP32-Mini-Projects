//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor gserial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/gpio.h"
#include "esp_log.h"
#include <dht.h>

#define DHT11_PIN 17
#define BUZZER_PIN 18
#define BUZZER_PIN_SEL (1ULL << BUZZER_PIN)

#define HUM_THRESHOLD 800
#define TEMP_THRESHOLD 250
