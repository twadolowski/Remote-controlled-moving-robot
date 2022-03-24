/**
* @file main.c
* @brief File containing the main function.
* 
*/
#include "movement_control.h"

/**
* @brief The main loop.
*
* @return NULL
*/
int main (void) {
	PIN_Init ();
	disable_motors();
   /* initialize all PINSs */


	move_forward();
 while(1){

	move_forward();
		DELAY(10000)
}
}

