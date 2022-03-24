# include "MKL05Z4.h"                        /* header with CMSIS */

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


typedef struct {
	GPIO_Type 	*gpio;        /* GPIO base pointer */
	PORT_Type 	*port;        /* PORT base pointer */
	uint32_t		clk_mask;     /* Mask for SCGC5 register */
	uint32_t  	pin;          /* Number of PIN */
} PinStruct_Type;


#define GPIO_MAX 13
static PinStruct_Type gpio[GPIO_MAX] = {
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 10},			/* LEFT */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 9},			/* RIGHT */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 8},			/* STOP */
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 11},			/* Dir1 */   
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 5},			/* Step1 */  
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 10},			/* Sleep1 */ 
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 12},			/* Rst1 */   
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 6},			/* En1 */
		{PTB, PORTB, SIM_SCGC5_PORTB_MASK, 11},			/* Dir2 */   
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 5},			/* Step2 */  
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 7},			/* Sleep2 */ 
		{PTA, PORTA, SIM_SCGC5_PORTA_MASK, 6},      /* Rst2 */   
    {PTB, PORTB, SIM_SCGC5_PORTB_MASK, 0},		  /* En2 */  
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

volatile static char uart_rx_cmd;

static uint8_t msTicks = 0;
static uint8_t newTick = 0;

void SysTick_Handler(void);
void SysTick_Handler(void) {
	msTicks++;
	newTick = 1;
	gpio[STEP1].gpio->PTOR |= 1UL << (gpio[STEP1].pin);
	gpio[STEP2].gpio->PTOR |= 1UL << (gpio[STEP2].pin);
}

int main (void) { 
	  SysTick_Config(1000000);
	  UART0_Init();
	  gpio_init();
		gpio_state(RST1, 1);
		gpio_state(SLEEP1, 1);
		

		gpio_state(RST2, 1);
		gpio_state(SLEEP2, 1);
	  while(1) {
				if(UART0->S1 & UART0_S1_RDRF_MASK)
				{
						uart_rx_cmd = UART0->D;
				}
				switch (uart_rx_cmd) 
				{
						case 'S':
							gpio_state(STOP, 0);
							gpio_state(LEFT, 1);
							gpio_state(RIGHT, 1);
						  gpio_state(EN1, 1);
						  gpio_state(EN2, 1);
							break;
						case 'F':
							gpio_state(STOP, 1);
							gpio_state(LEFT, 0);
							gpio_state(RIGHT, 0);
						  gpio_state(EN1, 0);
						  gpio_state(EN2, 0);
	            gpio_state(DIR1, 1);
		          gpio_state(DIR2, 0);
						  break;
						case 'R':
							gpio_state(STOP, 1);
							gpio_state(LEFT, 1);
							gpio_state(RIGHT, 0);
	            gpio_state(DIR1, 0);
		          gpio_state(DIR2, 0);
						  gpio_state(EN1, 0);
						  gpio_state(EN2, 0);
							break;
						case 'L':
							gpio_state(STOP, 1);
							gpio_state(LEFT, 0);
							gpio_state(RIGHT, 1);
	            gpio_state(DIR1, 1);
		          gpio_state(DIR2, 1);
						  gpio_state(EN1, 0);
						  gpio_state(EN2, 0);
							break;
						default:
							gpio_state(STOP, 1);
							gpio_state(LEFT, 1);
							gpio_state(RIGHT, 1);
	            gpio_state(DIR1, 1);
		          gpio_state(DIR2, 0);
						  gpio_state(EN1, 1);
						  gpio_state(EN2, 1);
				}
		}
}
