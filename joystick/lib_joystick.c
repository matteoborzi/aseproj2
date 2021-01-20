/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2021-01-20
** Last Version:        V1.01
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
  // Joystick initialization
	LPC_PINCON->PINSEL3 &= ~(3<<18);	//PIN mode GPIO (00b value per P1.25)
	LPC_PINCON->PINSEL3 &= ~(3<<20);	//PIN mode GPIO (00b value per P1.26)
	LPC_PINCON->PINSEL3 &= ~(3<<22);	//PIN mode GPIO (00b value per P1.27)
	LPC_PINCON->PINSEL3 &= ~(3<<24);	//PIN mode GPIO (00b value per P1.28)
	LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29)

	// GPIO direction as Input
	LPC_GPIO1->FIODIR   &= ~(1<<25);	//P1.25 Input (joysticks on PORT1 defined as Input) 
	LPC_GPIO1->FIODIR   &= ~(1<<26);	//P1.26 Input (joysticks on PORT1 defined as Input) 
	LPC_GPIO1->FIODIR   &= ~(1<<27);	//P1.27 Input (joysticks on PORT1 defined as Input) 
	LPC_GPIO1->FIODIR   &= ~(1<<28);	//P1.28 Input (joysticks on PORT1 defined as Input) 
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.29 Input (joysticks on PORT1 defined as Input) 

}

/*----------------------------------------------------------------------------
  Function that deinitializes joysticks (switching them off)
 *----------------------------------------------------------------------------*/
void joystick_deinit(void){
	LPC_GPIO1->FIODIR   |= (1<<25);
	LPC_GPIO1->FIODIR   |= (1<<26);
	LPC_GPIO1->FIODIR   |= (1<<27);
	LPC_GPIO1->FIODIR   |= (1<<28);
	LPC_GPIO1->FIODIR   |= (1<<29);
}
