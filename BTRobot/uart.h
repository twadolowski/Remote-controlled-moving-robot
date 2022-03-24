#ifndef _UART_H_
#define _UART_H_

#include "MKL05Z4.h"

void UART0_Init(void);
void UART0_Send(unsigned char data);
uint8_t UART0_IsDataReadyToRead(void);
uint8_t UART0_Read(void);

#endif
