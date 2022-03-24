#ifndef _PIT_H_
#define _PIT_H_

#include "MKL05Z4.h"

typedef void (*pit_callback)(void); 
void pit_init(uint32_t counter, pit_callback pcb);

#endif
