#ifndef _H_BITMAPS
#define _H_BITMAPS


/******************************************************************************
**	Color definitions
******************************************************************************/
#define BLACK			0x0000
#define PINK			0xF9CA
#define BLUE			0x3AD0
#define DARKBLUE	0x192C
#define WHITE			0xFFFF
#define GREEN 		0x4EA4
#define LGREEN		0x3481
#define DGREEN		0x1240
#define BROWN			0x9B47
#define GREY			0x73AE
#define DARKGREY	0x4208


/******************************************************************************
**	Player palettes and bitmaps
******************************************************************************/

// For each group: SOUTH, NORTH, EAST, WEST
const uint16_t palette[2][4][4] = {
	{	// palette[0]:	EXPLORE
		{BLACK, PINK, GREY, WHITE}, 
		{BLACK, WHITE, GREY, DARKGREY},
		{BLACK, WHITE, PINK, GREY},
		{BLACK, WHITE, PINK, GREY},	
	},
	
	{ // palette[1]:	MOVE
		{BLACK, PINK, BLUE, WHITE}, 
		{BLACK, WHITE, BLUE, DARKBLUE},
		{BLACK, WHITE, PINK, BLUE},
		{BLACK, WHITE, PINK, BLUE},
	}
};

const uint32_t slime4bit[4][16] = {
	{ // SOUTH
		0xFFFFFFFF, 0xFFFCFFFF, 0xFFF23FFF, 0xFFF23FFF, 
		0xFFC20FFF, 0xFF0A83FF, 0xFCAAA8FF, 0xF2BABA3F, 
		0xCACECE8F, 0xCABABA8F, 0xCA6AA68F, 0xCA955A8F, 
		0xF0AAA83F, 0xFF0003FF, 0xFFFFFFFF, 0xFFFFFFFF, },
	{	// NORTH
		0x55555555, 0x55545555, 0x55521555, 0x55521555, 
		0x55420555, 0x550A8155, 0x54AAA855, 0x52AAAA15, 
		0x4AAAAA85, 0x4EAAAAC5, 0x4FAAABC5, 0x4FFFFFC5, 
		0x50FFFC15, 0x55000155, 0x55555555, 0x55555555,	},
	{	// EAST
		0x55555555, 0x55551555, 0x5554C555, 0x5554C555, 
		0x5550C555, 0x554FF155, 0x553FFC55, 0x54FFFD15, 
		0x53FFF445, 0x53FFFDC5, 0x53FFEFC5, 0x54FFFA85, 
		0x553FFF15, 0x55400055, 0x55555555, 0x55555555, },
	{	// WEST
	  0x55555555, 0x55545555, 0x55531555, 0x55531555, 
		0x55530555, 0x554FF155, 0x553FFC55, 0x547FFF15, 
		0x511FFFC5, 0x537FFFC5, 0x53FBFFC5, 0x52AFFF15, 
		0x54FFFC55, 0x55000155, 0x55555555, 0x55555555, 
	},
};

/******************************************************************************
**	Tree palette and bitmap
******************************************************************************/
const uint16_t treePalette[4] = {DGREEN, WHITE, BROWN, LGREEN};

const uint32_t walls[16] = {
	0x57D557D5, 0x5FF55FF5, 0x7FFD7FFD, 0x7FC17FC1, 
	0xFCF0FCF0, 0xCFC0CFC0, 0xFF30FF30, 0xF3C0F3C0, 
	0xCF30CF30, 0xF300F300, 0xCCC0CCC0, 0xC000C000, 
	0x43014301, 0x50055005, 0x58255825, 0x5AA55AA5, 
};

#endif

/******************************************************************************
**                            End Of File
******************************************************************************/
