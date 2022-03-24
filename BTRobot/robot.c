#include "robot.h"
#include "uart.h"
#include "gpio.h"
#include "commands.h"
#include "pit.h"

static char uart_rx_cmd;

static unsigned char m1;
static unsigned char m2;


void robot_toggle(void);
void robot_toggle(void)
{
	  if (m1)
		{
		    gpio_toggle(STEP1);
		}
		if (m2)
		{
        gpio_toggle(STEP2);
		}
}

void robot_init(void)
{
    UART0_Init();
    gpio_init();
	  pit_init(79000, &robot_toggle);//79

    gpio_state(RST1, 1);
    gpio_state(SLEEP1, 1);

    gpio_state(RST2, 1);
    gpio_state(SLEEP2, 1);
    uart_rx_cmd = COMMAND_STOP;
	
		gpio_state(STOP, 1);
		gpio_state(LEFT, 1);
		gpio_state(RIGHT, 1);
		gpio_state(DIR1, 1);
		gpio_state(DIR2, 0);
		gpio_state(EN1, 1);
		gpio_state(EN2, 1);
	  m1 = 0;
	  m2 = 0;
}

void robot_process(void)
{
    if (UART0_IsDataReadyToRead()) {
        uart_rx_cmd = UART0_Read();
    }
    switch (uart_rx_cmd) {
    case COMMAND_STOP:
        gpio_state(STOP, 0);
        gpio_state(LEFT, 1);
        gpio_state(RIGHT, 1);
        gpio_state(EN1, 1);
        gpio_state(EN2, 1);
		    m1 = 0;
		    m2 = 0;
        break;
    case COMMAND_FORWARD:
        gpio_state(STOP, 1);
        gpio_state(LEFT, 0);
        gpio_state(RIGHT, 0);
        gpio_state(EN1, 0);
        gpio_state(EN2, 0);
        gpio_state(DIR1, 1);
        gpio_state(DIR2, 0);
		    m1 = 1;
		    m2 = 1;
        break;
    case COMMAND_RIGHT:
        gpio_state(STOP, 1);
        gpio_state(LEFT, 1);
        gpio_state(RIGHT, 0);
        gpio_state(DIR1, 0);
        gpio_state(DIR2, 0);
        gpio_state(EN1, 0);
        gpio_state(EN2, 0);
		    m1 = 1;
		    m2 = 1;
        break;
    case COMMAND_LEFT:
        gpio_state(STOP, 1);
        gpio_state(LEFT, 0);
        gpio_state(RIGHT, 1);
        gpio_state(DIR1, 1);
        gpio_state(DIR2, 1);
        gpio_state(EN1, 0);
        gpio_state(EN2, 0);
		    m1 = 1;
		    m2 = 1;
        break;
    default:
        gpio_state(STOP, 1);
        gpio_state(LEFT, 1);
        gpio_state(RIGHT, 1);
        gpio_state(DIR1, 1);
        gpio_state(DIR2, 0);
        gpio_state(EN1, 1);
        gpio_state(EN2, 1);
		    m1 = 0;
		    m2 = 0;
    }
}


