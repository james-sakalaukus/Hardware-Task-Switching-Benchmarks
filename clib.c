#include <clib.h>

/* 
 * Copies 'num' bytes from 'source' directly to 'dest'.
 * 'dest' is returned.
 */
char *memcpy(char *dest, const char *src, unsigned int num)
{
  unsigned int i;
  
  for(i=0;i<num;i++)
    dest[i] = src[i];
    
  return dest;
}

/*
 * Sets 'num' bytes of 'dest' to 'val'. 
 * 'dest' is returned.
 */
char *memset(char *dest, char val, unsigned int count)
{
  unsigned int i;
  
  for(i=0;i<count;i++)
    dest[i] = val;
    
  return dest;
}

unsigned int strlen(const char *str)
{
  unsigned int i = 0;
  
  while(1)
  {
    if(str[i] == NULL)
      break;
    else
      i++;
  }
  return i;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
