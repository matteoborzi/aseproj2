/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_labyrinth.c
** Last modified Date:  2021-01-12
** Correlated files:    labyrinth.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "labyrinth.h"

// Constants
//SOUTH = 0, NORTH, EAST, WEST
const int y_ver[4] = {	1, -1,	0,	0};
const int x_ver[4] = {	0,	0,	1, -1};

// Global variables
const char map[LENGTH][WIDTH] = {
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{0,0,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,1,0,1,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},	
	{1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,0,1,0,0,0,0,0,0,0,0,0,0,0,2},
};


unsigned int x = START_X;
unsigned int y = START_Y;
unsigned int current_direction;

unsigned int rotate (unsigned int next_direction){

	int i, j;
	uint8_t obstacle_found;
	uint8_t out_of_bounds;
	unsigned int distance;
	
	current_direction = next_direction;

	i = y;
	j = x;
	
	out_of_bounds = 0;
	distance = 0;
	obstacle_found = 0;
	
	while(obstacle_found == 0 && out_of_bounds == 0 && distance <=6){
		distance++;
		i = i + y_ver[next_direction];
		j = j + x_ver[next_direction];

		if(i < 0 || j < 0 || i >= LENGTH || j >= WIDTH){
			out_of_bounds = 1;
			distance += 0xFF;
		} else if(map[i][j] == 1){
			obstacle_found = 1;
		}
	}
	
	return distance;
}

void run (void) {
	y = y + y_ver[current_direction];		
	x = x + x_ver[current_direction];	
}

/**
 *	This function disables the INT0 button interrupt and enables interrupts
 *	for buttons KEY1 and KEY2.
 *		-	KEY1 has priority 1 (rotation stops any running action)
 *		-	KEY2 has priority 2
 */
void game_start(void) {
	/*
	game_started = 1;

	LPC_PINCON->PINSEL4   &= ~(1 << 20);		// External interrupt 0 pin disabled
  LPC_PINCON->PINSEL4    |= (1 << 22);    // External interrupt 1 pin selection
  LPC_PINCON->PINSEL4    |= (1 << 24);    // External interrupt 2 pin selection

  LPC_SC->EXTMODE = 0x6;									// Only EINT0 is disabled
	
	// INT0 button is not needed any more
	NVIC_DisableIRQ(EINT0_IRQn);						// Disable IRQ for EINT0 in nvic			

	// KEY1 button handles rotation
  NVIC_EnableIRQ(EINT1_IRQn);             // enable IRQ for EINT1 in nvic       
	NVIC_SetPriority(EINT1_IRQn, 1);				// priority is lower than RIT handler  		

	// KEY2 button handles running
  NVIC_EnableIRQ(EINT2_IRQn);             // enable IRQ for EINT2 in nvic       
	NVIC_SetPriority(EINT2_IRQn, 1);				// priority is lower than RIT handler 
	
	// Timers initialization
	init_timer(1,STEP_NCYCLES);							// Initialization of TIMER1 (1 sec)		
	init_timer(2,_1HZ_TIMER);								// Initialization of TIMER2 (10 Hz)		
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);

	// Reset and initialize LEDs
	LED_Out(0);
	rotate();
	*/
}


void game_end (void){
	/*
	game_started = 2;

	// Disable all interrupts
	NVIC_DisableIRQ(TIMER0_IRQn);
	NVIC_DisableIRQ(TIMER1_IRQn);
	NVIC_DisableIRQ(TIMER2_IRQn);
	NVIC_DisableIRQ(EINT0_IRQn);
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT2_IRQn);
	NVIC_DisableIRQ(RIT_IRQn);
	
	// Disable all timers
	disable_timer(0);
	disable_timer(1);
	disable_timer(2);
	
	// All LEDs blink endlessly at 1 Hz
	LPC_SC->PCLKSEL1  &=  ~(1<<14);
	init_timer(3,_1HZ_TIMER);
	reset_timer(3);
	LED_Out(0x2F);
	enable_timer(3);	
	*/
}

/******************************************************************************
**                            End Of File
******************************************************************************/
