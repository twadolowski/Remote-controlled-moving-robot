#define BAUD_RATE 9600

#include "uart.h"

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

void UART0_Send(unsigned char  data) {
    while(!(UART0->S1 & UART0_S1_TDRE_MASK));
    UART0->D = data;
}

uint8_t UART0_IsDataReadyToRead(void) 
{
    return UART0 -> S1 & UART0_S1_RDRF_MASK;
}

uint8_t UART0_Read(void) 
{
    return UART0 -> D;
}
