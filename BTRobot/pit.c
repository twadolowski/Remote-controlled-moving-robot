#include "pit.h"

static pit_callback pcb_reg;

void pit_init(uint32_t counter, pit_callback pcb)
{
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    PIT->MCR |= PIT_MCR_FRZ_MASK;
    PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(counter);
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK; 
    NVIC_SetPriority(PIT_IRQn, 1); 
    NVIC_ClearPendingIRQ(PIT_IRQn); 
    NVIC_EnableIRQ(PIT_IRQn);    
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; 
	  pcb_reg = pcb;
}

void PIT_IRQHandler(void);
void PIT_IRQHandler(void) 
{
	  pcb_reg();
	  if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
        PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; 
    }
}
