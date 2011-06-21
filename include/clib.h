#ifndef CLIB_H
#define CLIB_H

#define NULL '\0'

/* memory functions */
char *memcpy(char *dest, const char *src, unsigned int num);
char *memset(char *dest, char val, unsigned int count);

/* string functions */
unsigned int strlen(const char *str);

/* x86 in/out i/o functions */
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif
