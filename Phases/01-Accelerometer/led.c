/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file led.c
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing definitions for LEDs.
 * @ver 0.1
 */

#include "led.h"    /* header with led declarations */

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
/**
 * @brief LEDs available on eval board.
 */
#ifdef FRDM_KL05Z
# define LED_N   3
	static PinStruct_Type led[LED_N] = {
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 8},			/* Red */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 9},			/* Green */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10}			/* Blue */
	};
#endif /* FRDM_KL05Z */

void LED_Init(void) {  
  
  for(int i = 0; i < LED_N; i++) {
    SIM->SCGC5 |= led[i].clk_mask;              /* connect CLOCK to port */
	  led[i].port->PCR[led[i].pin] = PORT_PCR_MUX(1UL); /* set MUX to GPIO */
	  led[i].gpio->PDDR |= MASK(led[i].pin);            /* set as OUTPUT   */
	  led[i].gpio->PSOR |= MASK(led[i].pin);            /* OFF as default  */
  } /* do for all leds */
}

void LED_Ctrl(LedColor_Type color, LedState_Type led_state) {  

  switch (led_state) 
  {
    case LED_OFF:     led[color].gpio->PSOR |= MASK(led[color].pin);
      break;
    case LED_ON:      led[color].gpio->PCOR |= MASK(led[color].pin);
      break;
    case LED_TOGGLE:  led[color].gpio->PTOR |= MASK(led[color].pin);
      break;
  } 
}

void LED_Blink (LedColor_Type color, uint32_t time) {
    
  LED_Ctrl(color, LED_ON);
  DELAY(time)
  LED_Ctrl(color, LED_OFF);
  DELAY(time)
}

void LED_Welcome (void) {
  
  for(int i = 0; i < LED_N; i++) LED_Blink((LedColor_Type)i, 100);
}
