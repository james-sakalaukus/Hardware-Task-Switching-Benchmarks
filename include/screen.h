/* screen.h
 * 
 * This file provides basic VGA functionality.  The kernel should call
 * init_video() before using these functions.
 * 
 * VGA looks like an 80x25 matrix of 16-bit values
 *
 */

#ifndef SCREEN_H
#define SCREEN_H

/* VGA colors */
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define LIGHTBROWN 14
#define WHITE 15


/* Standard location for VGA video memory */
#define VIDEOMEMORY 0x0B8000

/* Pointer to modify video memory */
extern char *videoMemPtr;

/* VGA uses 4 bits to represent the foreground, and four bits to represent
 * the background color for a tile. Initialize it to white on black */
extern char textColor;

/* Use these to remember where the cursor is on the screen */
extern int cursorX;
extern int cursorY;

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(void);

/* Clears the screen */
void cls();

/* Puts a single character on the screen */
void putch(char c);

/* Uses the above routine to output a string... */
void puts(char *text);

/* Sets the forecolor and backcolor */
void settextcolor(char forecolor, char backcolor);

#endif
