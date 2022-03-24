/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *                                                   *
 ******************************************************************************/

/**
 * @file movement_constrols.h
 * @brief File containing enums, structures and declarations for control pins of the step motors.
 */

#ifndef MOVEMENT_CONTROL_H
#define MOVEMENT_CONTROL_H

#include "frdm_bsp.h"

/******************************************************************************\
* Global definitions
\******************************************************************************/

/**
 * @brief Pin State Types.
 */
typedef enum {
	PIN_OFF 			= (uint8_t)0,
	PIN_ON 				= (uint8_t)1,
	PIN_TOGGLE 		= (uint8_t)2
} PinState_Type;
/**
 * @brief Led Color Types.
 */
typedef enum {
	En1 		= (uint8_t)0,
	En2		= (uint8_t)1,
	Dir1		= (uint8_t)2,
	Dir2		= (uint8_t)3,	
	Step1		= (uint8_t)4,
	Step2		= (uint8_t)5
	
} PinName_Type;
/**
 * @brief Structure containing info about pin.
 */
typedef struct {
	GPIO_Type 	*gpio;        /* GPIO base pointer */
	PORT_Type 	*port;        /* PORT base pointer */
	uint32_t		clk_mask;     /* Mask for SCGC5 register */
	uint8_t  		pin;          /* Number of PIN */
} PinStruct_Type;
/**
 * @brief control PIN initialization.
 */
void PIN_Init (void);
/**
 * @brief Control choosen PIN.
 *
 * @param Pin Name.
 * @param State of a PIN.
 */
void PIN_Ctrl(PinName_Type pin_name, PinState_Type pin_state);
/**
 * @brief Disable both motors.
 */
void disable_motors(void);
void enable_motors(void);

/**
 * @brief Move both motors one step forward.
 */

void move_forward(void);


#endif /* MOVEMENT_CONTROL_H */
