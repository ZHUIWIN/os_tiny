#ifndef _ALLH_
#define _ALLH_


#define VGA_BASE 0xb8000
#define WHITE 0x7


//count idle colock
unsigned long TSC1,TSC1_pev;
unsigned long TSC2,TSC2_pev;


int row_now=1,col_now=0;

unsigned long  time_count=0;
unsigned long  idle_count=0;
unsigned short VGA_rows=25;
unsigned short VGA_cols=80;

unsigned long stack_esp;
unsigned long stack_ebp;

int tasknow=0;
int taskold=0;


void put_char(char c, char color, int row, int col);
void put_chars(char *msg, char color, int *_row, int *_col);
void clear_screen(void);
void print_time();
/*
void printf_system(const char *msg, ...);
void int2char(int num,char * tochar);


void create_task(int id,void *func);
void delete_queue(int id);
void check_queue(int id);
void check_sleep_queue(int id);
void delete_sleep_queue(int id);
*/
#endif
