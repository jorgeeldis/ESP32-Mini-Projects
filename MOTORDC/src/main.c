//* FULLY WORKING

// Recordar quitar otros proyectos del workspace, hacer build y luego upload, ver en el monitor gserial para los prints

#include <stdio.h>             // Libreria inicial para el codigo de C
#include <stdlib.h>            // Libreria inicial para el codigo de C
#include "freertos/FreeRTOS.h" // Libreria para el sistema operativo de ESP32
#include "freertos/task.h"     // Libreria que nos permite crear tasks
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define GPIO_PWM0A_OUT 15
#define GPIO_PWM0B_OUT 16

static void mcpwn_example_gpio_initialize(void)
{

    printf("inicializando mcpwm gpio.....");
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A_OUT);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B_OUT);
}
    static void brushed_motor_forward(mcpwm_unit_t mcpwm_num, mcpwm_unit_t timer_num, float duty_cycle)
    {
        cpm set.signal.low(mepem nus, timer nun, CPW OPR 8);
        Icpwn_set duty(ncpwn num, tiner_nun, ACPHMLOPRA, duty cycle);
        micpwm_set duty type(acpwm nun, tiser num, ACPWRLOPR_A, MCPWM DUTY.MODE 6);
    }
        /* Motor rota en direccién del reloj, con ciclo de trabajo = duty % */

        static void brushed_motor_forward(mcpym_unit_t mepwn_num, mcpwm tiner t timer_num, float duty cycle)
        {
            Iicpwm_set_signal_low(mcpwm_num, timer_nun, MCPWM_OPR_B);
            incpwm_set_duty(mepwn_num, timer_num, HCPHlt OPR A, duty cycle);
            ncpwm_set_duty_type(mcpwm_num, timer_num, ACPWH_OPRA, MCPHM DUTY MODE_9);
        }
        /* Motor rota en direccién contraria del reloj, con ciclo de trabajo = duty % */

        static void brushed_motor_backward(ncpwn unit t mepwn_num, mcpyn tiner t timer nun, float duty cycle)

        {
            mcpwm_set_signal_low(mcpwm_num, tiner_num, NCPHM_OPR A);
            mepwn_set_duty(ncpwm_num, timer_nun, HCPW_OPRB, duty cycte);
            mcpwn_set_duty_type(mcpwn num, timer num, HCPW_OPR B, MCPWM DUTY MODE 0);
        }

        y

            /* parada de notor */
            static void brushed
            motor_stop(mcpwn_unit t mepwm_num, mcpwm timer t timer_num)

        {
            Incpwm_set_signal_low(mcpwm num, timer_num, MCPWM_OPR_A);
                iicpwm_set_signal_low(mcpwm_num, timer_num, MCPHM_OPR_B);
}