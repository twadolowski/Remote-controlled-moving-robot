#include "controller.h"
#include "uart.h"
#include "gpio.h"
#include "commands.h"
#include "accelerometer.h"

void controller_init(void)
{
    UART0_Init();
    gpio_init();
    accelerometer_init();
}

void controller_process(void)
{
    accelerometer_vector v =  accelerometer_read();
    if (v.y > -0.02f) {
        gpio_state(STOP, 0);
        gpio_state(LEFT, 1);
        gpio_state(RIGHT, 1);
        UART0_Send(COMMAND_STOP);
    } else {
        gpio_state(STOP, 1);
        if ((v.x < 0.1f) && (v.x > -0.1f)) {
            gpio_state(LEFT, 0);
            gpio_state(RIGHT, 0);
            UART0_Send(COMMAND_FORWARD);
        } else {
            if (v.x < 0) {
                UART0_Send(COMMAND_RIGHT);
                gpio_state(LEFT, 1);
                gpio_state(RIGHT, 0);
            } else {
                UART0_Send(COMMAND_LEFT);
                gpio_state(LEFT, 0);
                gpio_state(RIGHT, 1);
            }
        }
    }
}



