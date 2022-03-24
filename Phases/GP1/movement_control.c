/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file movement_constrols.c
 */

#include "movement_control.h"  /* header with led declarations */

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
/**
 * @brief chosen pins on portB to control the movement of both step motors
 */
#ifdef FRDM_KL05Z
# define PIN_N   6
	static PinStruct_Type pin[PIN_N] = {
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 3},			/* En1*/
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 4},			/* En2 */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 11},			/* Dir1 */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10},			/* Dir2 */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 7},			/* Step1 */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 6}			/* Step2 */
	};
#endif /* FRDM_KL05Z */

void PIN_Init(void) {  
  
  for(int i = 0; i < PIN_N; i++) {
    SIM->SCGC5 |= pin[i].clk_mask;              /* connect CLOCK to port */
	  pin[i].port->PCR[pin[i].pin] = PORT_PCR_MUX(1UL); /* set MUX to GPIO */
	  pin[i].gpio->PDDR |= MASK(pin[i].pin);            /* set as OUTPUT   */
	  pin[i].gpio->PSOR |= MASK(pin[i].pin);            /* OFF as default  */
  } /* do for all leds */
}

void PIN_Ctrl(PinName_Type pin_name, PinState_Type pin_state) {  

  switch (pin_state) 
  {
    case PIN_OFF:     pin[pin_name].gpio->PSOR |= MASK(pin[pin_name].pin);
      break;
    case PIN_ON:      pin[pin_name].gpio->PCOR |= MASK(pin[pin_name].pin);
      break;
    case PIN_TOGGLE:  pin[pin_name].gpio->PTOR |= MASK(pin[pin_name].pin);
      break;
  } 
}
void disable_motors(void)
{
	  PIN_Ctrl(En1, PIN_OFF);
	  PIN_Ctrl(En2, PIN_OFF);
}
void enable_motors(void)
	{
	  PIN_Ctrl(En1, PIN_ON);
	  PIN_Ctrl(En2, PIN_ON);
}
	
void move_forward(void)
	{
    PIN_Ctrl(Dir1, PIN_ON);
		PIN_Ctrl(Dir2, PIN_ON);
for(uint8_t x=0;x<200;x++)
	{
		PIN_Ctrl(Step1, PIN_ON);
		PIN_Ctrl(Step2, PIN_ON);
		DELAY(500)
		PIN_Ctrl(Step1, PIN_OFF);
		PIN_Ctrl(Step2, PIN_OFF);
		DELAY(500)
	}
}
