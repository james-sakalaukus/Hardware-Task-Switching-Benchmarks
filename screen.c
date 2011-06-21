/* screen.h
 * 
 * This file provides basic VGA functionality.  The kernel should call
 * init_video() before using these functions.
 * 
 * VGA looks like an 80x25 matrix of 16-bit values
 * 
 */
 
#include <clib.h>
#include <screen.h>

/* Pointer to modify video memory */
char *videoMemPtr = (char*)VIDEOMEMORY;

/* VGA uses 4 bits to represent the foreground, and four bits to represent
 * the background color for a tile. Initialize it to white on black */
char textColor = (BLACK << 4) | (WHITE & 0x0F);


/* Use these to remember where the cursor is on the screen */
int cursorX = 0;
int cursorY = 0;


/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = cursorY * 80 + cursorX;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
  unsigned int i;

  // Sets the entire screen to spaces in current color
  for(i = 0; i < 25*80; i++)
  {
    videoMemPtr[i]= textColor;
    videoMemPtr[i+1]= 0x20;
  }
    // Update virtual cursor, and then move the hardware cursor
    cursorX = 0;
    cursorY = 0;
    move_csr();
}

/* Puts a single character on the screen */
void putch(char c)
{
  int i;
  
  // backspace
  if(c == 0x08)
  {
    if(cursorX != 0) 
      cursorX--;
  }
  // tab - increment cursorX, but make it divisible by 8 
  else if(c == 0x09)
  {
    cursorX = (cursorX + 8) & ~(8 - 1);
  }
  // carriage return
  else if(c == '\r')
  {
    cursorX = 0;
  }
  // newline
  else if(c == '\n')
  {
    cursorX = 0;
    cursorY++;
  }
  // Any character greater than and including a space, is a
  //  printable character. Index = [(y * width) + x] 
  else if(c >= ' ')
  {
    videoMemPtr[(cursorY * 80) + cursorX+1] = textColor;
    videoMemPtr[(cursorY * 80) + cursorX] = c;
    cursorX+=2;
  }

  // If the cursor has reached the edge of the screen's width, newline
  if(cursorX >= 80)
  {
    cursorX = 0;
    cursorY++;
  }

  // screen is full, scroll text up one line
  if(cursorY == 25)
  {
    // copy row1 to row0, etc.
    memcpy (videoMemPtr, videoMemPtr + 160, 160 * 24);
    
    // set last row to blank character
    for(i=0;i<80;i++)
    {
      memset (videoMemPtr + (25 * 160)+i, textColor, 1);
      memset (videoMemPtr + (25 * 160)+1+i, 32, 1);
    }
    cursorY = 24;
  }

    move_csr();
}

/* Uses the putch() to output a string */
void puts(char *text)
{
    unsigned int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

/* Sets the forecolor and backcolor */
void settextcolor(char forecolor, char backcolor)
{
    /* Top 4 bits are background, bottom 4 bits are foreground */
    textColor = (backcolor << 4) | (forecolor & 0x0F);
}


