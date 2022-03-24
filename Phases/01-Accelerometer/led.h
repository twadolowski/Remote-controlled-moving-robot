/******************************************************************************
 * This file is a part of the SM2 Tutorial (C).                               *
 ******************************************************************************/

/**
 * @file led.h
 * @author Koryciak
 * @date Sep 2020
 * @brief File containing enums, structures and declarations for LEDs.
 * @ver 0.1
 */

#ifndef LED_H
#define LED_H

#include "frdm_bsp.h"

/******************************************************************************\
* Global definitions
\******************************************************************************/
#define HEART_BEAT		LED_RED   /* program alive identifier */
#define BEAT_TIME     500
/**
 * @brief Led State Types.
 */
typedef enum {
	LED_OFF 			= (uint8_t)0,
	LED_ON 				= (uint8_t)1,
	LED_TOGGLE 		= (uint8_t)2
} LedState_Type;
/**
 * @brief Led Color Types.
 */
typedef enum {
	LED_RED 		= (uint8_t)0,
	LED_GREEN		= (uint8_t)1,
	LED_BLUE		= (uint8_t)2
} LedColor_Type;
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
 * @brief LEDs initialization.
 */
void LED_Init (void);
/**
 * @brief Control choosen LED.
 *
 * @param Color of a LED.
 * @param State of a LED.
 */
void LED_Ctrl(LedColor_Type color, LedState_Type led_state);
/**
 * @brief Blink choosen LED one time.
 *
 * @param Color of LED.
 */
void LED_Blink (LedColor_Type color, uint32_t time);
/**
 * @brief Welcome sequence.
 */
void LED_Welcome (void);

#endif /* LED_H */
