#include "gpio.h"

#define GPIO_MAX 13
static PinStruct_Type gpio[GPIO_MAX] = {
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10},   /* LEFT */
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 9},    /* RIGHT */
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 8},    /* STOP */
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 11},   /* Dir1 */   
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 5},    /* Step1 */  
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 10},   /* Sleep1 */ 
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 12},   /* Rst1 */   
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 6},    /* En1 */
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 11},   /* Dir2 */   
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 5},    /* Step2 */  
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 7},    /* Sleep2 */ 
        {PTA, PORTA, SIM_SCGC5_PORTA_MASK, 6},    /* Rst2 */   
        {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 0},    /* En2 */  
};

void gpio_state(uint32_t pin, uint8_t state)
{
    if (state)
        {
            gpio[pin].gpio->PSOR |= 1UL << (gpio[pin].pin);
        } else {
              gpio[pin].gpio->PCOR |= 1UL << (gpio[pin].pin);
        }
}

void gpio_init(void) {  
    for(int i = 0; i < GPIO_MAX; i++) {        
          SIM->SCGC5 |= gpio[i].clk_mask;
          gpio[i].port->PCR[gpio[i].pin] = PORT_PCR_MUX(1UL); 
          gpio[i].gpio->PDDR |= 1ul << (gpio[i].pin);           
          gpio[i].gpio->PSOR |= 1ul << (gpio[i].pin);           
    } 
}

void gpio_toggle(uint32_t pin)
{
      gpio[pin].gpio->PTOR |= 1UL << (gpio[pin].pin);
}

