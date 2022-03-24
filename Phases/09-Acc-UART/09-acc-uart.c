#include "MKL05Z4.h"                        /* header with CMSIS */
#include "i2c.h"

#define LEFT 0
#define RIGHT 1
#define STOP 2


typedef struct {
	GPIO_Type 	*gpio;        /* GPIO base pointer */
	PORT_Type 	*port;        /* PORT base pointer */
	uint32_t		clk_mask;     /* Mask for SCGC5 register */
	uint32_t  		pin;          /* Number of PIN */
} PinStruct_Type;


#define GPIO_MAX 3
static PinStruct_Type gpio[GPIO_MAX] = {
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10},			/* LEFT */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 9},			/* RIGHT */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 8},			/* STOP */
	};
		

void gpio_state(uint32_t pin, uint8_t state);
void gpio_state(uint32_t pin, uint8_t state)
{
    if (state)
		{
		    gpio[pin].gpio->PSOR |= 1UL << (gpio[pin].pin);
		} else {
			  gpio[pin].gpio->PCOR |= 1UL << (gpio[pin].pin);
		}
}

void gpio_init(void);
void gpio_init(void) {  
    for(int i = 0; i < GPIO_MAX; i++) {        
		    SIM->SCGC5 |= gpio[i].clk_mask;
	      gpio[i].port->PCR[gpio[i].pin] = PORT_PCR_MUX(1UL); 
	      gpio[i].gpio->PDDR |= 1ul << (gpio[i].pin);           
	      gpio[i].gpio->PSOR |= 1ul << (gpio[i].pin);           
    } 
}

#define BAUD_RATE 9600

void UART0_Init(void);
void UART0_Init(void)
{
	uint32_t divisor, osr;
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
  
  PORTB->PCR[1] = PORT_PCR_MUX(2); 
  PORTB->PCR[2] = PORT_PCR_MUX(2);   
	
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	
	osr = 32;
	UART0->C4 |= UART0_C4_OSR(osr-1);
	divisor = SystemCoreClock / (osr * BAUD_RATE);
	UART0->BDH = UART0_BDH_SBR(divisor >> 8);
	UART0->BDL = UART0_BDL_SBR(divisor);
	
	UART0->BDH |= UART0_BDH_SBNS_MASK;

	UART0->C2 = UART0_C2_TE_MASK | UART0_C2_RE_MASK;
}

void UART0_Send(uint8_t data);
void UART0_Send(uint8_t data) {
	while(!(UART0->S1 & UART0_S1_TDRE_MASK));
	UART0->D = data;
}

static uint8_t msTicks = 0;
static uint8_t newTick = 0;

void SysTick_Handler(void);
void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
}



int main (void) { 
	  uint8_t arrayXYZ[6];
	  SysTick_Config(1000000); 
	  UART0_Init();
	  gpio_init();
	  I2C_Init();
		I2C_WriteReg(0x1D, 0x2A, 1);	 		// Set ACTIVE bit in CTRL_REG1 in MMA8451
	  while(1) {
  			__WFI();
			  if (newTick)
				{
						if (!(msTicks % 10))
						{

     		        for (int i =0; i < 3; i++)
		            {
					          I2C_ReadRegBlock(0x1D, 0x01, 6, arrayXYZ);
								}
								float x = ((float)((int16_t)((arrayXYZ[0]<<8)|arrayXYZ[1])>>2)/4096);
								float y = ((float)((int16_t)((arrayXYZ[2]<<8)|arrayXYZ[3])>>2)/4096);
						
								if (y > -0.02f)
								{
								    gpio_state(STOP, 0);
								    gpio_state(LEFT, 1);
									  gpio_state(RIGHT, 1);
									  UART0_Send('S');
								} else {
									  gpio_state(STOP, 1);
								    if ((x < 0.1f) && (x > -0.1f))
										{
												gpio_state(LEFT, 0);
												gpio_state(RIGHT, 0);
												UART0_Send('F');
										}
										else
										{
												if (x < 0)
												{
														UART0_Send('R');
														gpio_state(LEFT, 1);
														gpio_state(RIGHT, 0);
												}
												else
												{
														UART0_Send('L');
														gpio_state(LEFT, 0);
														gpio_state(RIGHT, 1);
												}
										}
							  }								
						}
						newTick = 0;
				}
  	}
}
