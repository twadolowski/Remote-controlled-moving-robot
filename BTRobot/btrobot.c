#include "MKL05Z4.h"
#include "i2c.h"
#include "gpio.h"
#include "robot.h"
#include "controller.h"
#include "pit.h"

static uint8_t msTicks = 0;
static uint8_t newTick = 0;

void SysTick_Handler(void);
void SysTick_Handler(void) {
    msTicks++;
    newTick = 1;
}

#define ROBOT_CODE
//#define CONTROLLER_CODE

#if 1
int main() 
{
    SysTick_Config(1000000);
#ifdef ROBOT_CODE
    robot_init();
    while (1)
    {
        robot_process();
    }
#else
#ifdef CONTROLLER_CODE
    controller_init();
    while (1) 
    {
        __WFI();
        if (newTick) 
				{
            if (!(msTicks % 10)) 
						{
                controller_process();
            }
            newTick = 0;
        }
    }
#endif
#endif
}
#endif

