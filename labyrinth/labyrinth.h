/*----------------------------------------------------------------------------
	Here the methods and the functions that modify the status of the game
	are defined, with constants like the map matrix and its dimensions
 *----------------------------------------------------------------------------*/

#define	LENGTH				13
#define	WIDTH 				15
#define	START_X				7
#define	START_Y				7
	
enum direction { NORTH = 0, EAST, SOUTH, WEST};

// Global variables
extern unsigned int game_started;
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

// Game methods
void game_start(void);
void game_end(void);

void rotate(void);
void run(void);
