#ifndef _PRINTF_H_
#define _PRINTF_H_

#include <stdarg.h>

#define printf printf_system

/*
#define printf(format, ...) printf_system(format, __VA_ARGS__)
#define printf1(format, ...) printf_system1(format, __VA_ARGS__)
#define printf2(format, ...) printf_system2(format, __VA_ARGS__)
*/
#define VGA_BASE 0xb8000

extern int row_now;
extern int col_now;

void next_screen(void);
void int2char(int p_num,char * tochar);

void printf(const char *msg, ...);
void printf1(const char *msg, ...);
void printf2(const char *msg, ...);

#endif