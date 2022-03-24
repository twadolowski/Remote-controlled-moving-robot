#ifndef _GPIO_H_
#define _GPIO_H_

#include "MKL05Z4.h"                       

#define LEFT 0
#define RIGHT 1
#define STOP 2

#define DIR1 3
#define STEP1 4
#define SLEEP1 5
#define RST1 6
#define EN1 7
#define DIR2 8
#define STEP2 9
#define SLEEP2 10
#define RST2 11
#define EN2 12


#define GPIO_MAX 13

typedef struct {
	GPIO_Type *gpio;       /* GPIO base pointer */
	PORT_Type *port;       /* PORT base pointer */
	uint32_t clk_mask;     /* Mask for SCGC5 register */
	uint32_t pin;          /* Pin number */
} PinStruct_Type;

void gpio_state(uint32_t pin, uint8_t state);
void gpio_toggle(uint32_t pin);
void gpio_init(void);

#endif
