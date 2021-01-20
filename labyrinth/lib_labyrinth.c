/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_labyrinth.c
** Last modified Date:  2021-01-20
** Correlated files:    labyrinth.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "labyrinth.h"
#include "../joystick/joystick.h"
#include "../GLCD/GLCD.h"

// Constants
//SOUTH = 0, NORTH, EAST, WEST
const int y_ver[4] = {	1, -1,	0,	0};
const int x_ver[4] = {	0,	0,	1, -1};

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

// Local variables
unsigned int x = START_X;
unsigned int y = START_Y;
unsigned int current_direction;
unsigned int current_distance;

// Extern variables
extern unsigned int game_status;
extern unsigned int current_mode;


/******************************************************************************
* Function Name  : rotate
* Description    : Handles logic for player rotation and its display placement
* Input          :	- next_direction: chosen direction for rotation
* Output         :	- distance from next obstacle if found within 6 steps
*										- distance + 0xFF: if obstacle is not found
* Return				 : None
*******************************************************************************/
void rotate (unsigned int next_direction){
	int i, j;
	uint8_t obstacle_found;
	uint8_t out_of_bounds;
	unsigned int distance;
	
	current_direction = next_direction;

	Print_Player(x,y,next_direction,current_mode);
	
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
	
	if(distance<=6 && obstacle_found == 1)
		Print_Wall(j,i);
	
	current_distance = distance;
}


/******************************************************************************
* Function Name  : run
* Description    : Game logic for player step and its display
* Return         : None
*******************************************************************************/
void run (void) {
	if(current_distance > 0xFF){
		current_distance -= 0xFF;
	}
	
	if(current_distance > 1) {
		Remove_Player(x,y,White);

		y = y + y_ver[current_direction];		
		x = x + x_ver[current_direction];	

		if(map[y][x] == 2){
			Game_End();
		} else {
			Print_Player(x,y, current_direction,0);
		}
	}
}


/******************************************************************************
* Function Name  : change_mode
* Description    : Switch mode between EXPLORE and MOVE and display player
* Return         : None
*******************************************************************************/
void change_mode(void){
	current_mode = (current_mode+1)%2;
	Print_Player(x,y,current_direction,current_mode);
}


/******************************************************************************
* Function Name  : Game_Init
* Description    : Game initialization after SystemInit
* Return         : None
*******************************************************************************/
void Game_Init(void){
	joystick_deinit();
	
	game_status = 0;
	LCD_Clear(Black);
	
	GUI_Text(16,4, (uint8_t *) "Blind Labyrinth", Yellow, Black, 2);
		
	Print_Map(240,208,0,40,White);
	
	// CLEAR button coordinates: (8,260),(112,260),(8,304),(112,304)
	Print_Button(8,260,44,104,(uint8_t*) "Clear",Yellow, Black,16,6);
	
	// RESTART button coordinates: (128,260),(232,260),(128,304),(232,304)
	Print_Button(128,260,44,104, (uint8_t*) "Restart", Yellow, Black,2,6);
	
	// START text area
	GUI_Text(8,96, (uint8_t *) "Touch here", Black, White, 3);
	GUI_Text(32,144, (uint8_t *) "to start", Black, White, 3);
}

/******************************************************************************
* Function Name  : Game_Start
* Description    : Initialize game logic and joystick
* Return         : None
*******************************************************************************/
void Game_Start(void) {
	game_status = 1;
	x = START_X;
	y = START_Y;
	current_direction = SOUTH;
	current_mode = EXPLORE;

	// Joystick initialization
	joystick_init();	

	// Screen initialization
	Print_Map(240,208,0,40,White);
	Print_Player(x,y,current_direction,current_mode);
}


/******************************************************************************
* Function Name  : Game_End
* Description    : Set victory screen up and disable joystick
* Return         : None
*******************************************************************************/
void Game_End (void){
	game_status = 2;

	joystick_deinit();
	Print_Map(240,208,0,40,White);
	GUI_Text(18,80, (uint8_t *) "VICTORY", Black, White, 4);
	GUI_Text(40,144, (uint8_t *) "Press RESET or RESTART",Black, White, 1);
	GUI_Text(68,160, (uint8_t *) "for a new game",Black, White, 1); 
	Print_Player(7,9,SOUTH,MOVE);
}

/******************************************************************************
* Function Name  : Game_Clear
* Description    : Reset map display and draws sprite in its currnent
*									 position and direction
* Return         : None
*******************************************************************************/
void Game_Clear(void){
	Print_Map(240,208,0,40,White);
	Print_Player(x,y,current_direction,current_mode);
}
/******************************************************************************
**                            End Of File
******************************************************************************/
