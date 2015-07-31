#include "all.h"
#include "task.h"

#include "mem.c"
#include "semaphore.c"
#include "printf.c"
#include "alltask.c"


void clear_screen(void) {
	int row, col;
	unsigned short *ptr = (unsigned short *)VGA_BASE;
	for(row=0; row< 25; row++) {
	    for (col=0; col< 80; col++) {
		(*ptr++) = 0;
	    }
	}
}

void put_char(char c, char color, int row, int col) {
	unsigned char *ptr = (unsigned char *)VGA_BASE;
	unsigned short value;

	ptr[(row*80+col)*2] = c;
	ptr[(row*80+col)*2+1] = color;	
}

void put_chars(char *msg, char color, int *_row, int *_col){
	char *ptr=msg;
	char c;
	int row, col;
	
	row = *_row;	col = *_col;
	c = *ptr;
	while (c!='\0'){
	    if ( col==80 ) {	col = 0;	row ++;	}
	    if ( row==25 ) row = 0;

	    put_char(c, color, row, col++);	    
	    c = *(++ptr);
	}
	
}
void print_time(){
    char time[11];
    int tmp=time_count++,i = 0;
    
    for(i=0;i<10;i++) time[i]=' ';
    int min = tmp/60;
    int second = tmp%60;
    time[10]='\0';time[9]='S';
    time[8]='0'+ second%10;
    time[7]='0'+ second/10;
    time[6]=' ';time[5]='M';
    i = 4;
    while(min>0){
        time[i]='0'+min%10;
        min /=10;
        i--;
    }
    
    int row=0,col=70; put_chars(time,WHITE,&row,&col);
}

void print_tsc(){
    char time[21];int i;
    for(i=0;i<16;i++) time[i]=' ';
    time[15] ='c';time[16] ='y';time[17] ='c';time[18] ='l';time[19] ='e';
    time[20] = '\0';
    long t1 = TSC1-TSC1_pev;
    long t2 = TSC2-TSC2_pev;
    i=14;
    if(t1 < 0) {t1=-t1;time[i]='-';i--;}
    while(t1>0){
        time[i]='0'+t1%10;
        t1 /=10;
        i--;
    }
    while(t2>0){
        time[i]='0'+t2%10;
        t2 /=10;
        i--;
    }
    int row = 0,col  = 40;
    put_chars(time,WHITE,&row,&col);
}


int timer(){
    print_time();int i=0;
    for(i = 0;i<10;i++){
        if(ALLTASK[i]->idle>0)
            ALLTASK[i]->idle--;
        if(ALLTASK[i]->timer>0)
            ALLTASK[i]->timer--;
        if(ALLTASK[i]->sleeptime > 0)
            ALLTASK[i]->sleeptime--;
    }
    //schedule();抢占
    for(i = 0;i<10;i++){
        if(ALLTASK[i]->timer == 0){
            ALLTASK[i]->timer = -1;
            if(tasknow != i &&ALLTASK[i]->esp != 0 ) myswitch(i);
        }
    }
    if(tasknow == 9) idle_count++;
    int tmp_row = row_now;
    int tmp_col = col_now;
    row_now = 0;col_now = 30;
    printf_system("%2d%CPU ",100-(100*idle_count)/time_count);    
    row_now = tmp_row; 
    col_now = tmp_col;
    //保存当前打印的地址，打印出CPU利用率
    schedule();
}

int myMain(void){
    int i = 0;
    MEM =  &_end+0x2000/sizeof(int);
    listaddr = MEM;
    init_mem();
    for(i=0;i<10;i++){
        ALLTASK[i] = mymalloc(sizeof(tsk_str)/sizeof(int)+1);
    }

    init_all();
    init_RR_Queue();
    init_sleep_queue();
    init_semaphore();
    
    create_task(1,myTask1);
    create_task(6,myTask6);
    create_task(7,myTask7);
    create_task(8,myTask8);
    //create_task(4,myTask4);
    //create_task(5,myTask5);
    //create_task(3,myTask3);ALLTASK[3]->period = 20;
    create_task(9,idle_task);
    
	char *message1 = "********************************\0";
	char *message2 = "*        HELLO WORLD!          *\0";
	char *message3 = "*        ALLTASK OVER!         *\0";
	int row=0,col=0;

	clear_screen();

	printf_system("myMain:The test for printf!\n");
	printf_system("%d \n",ALLTASK[3]->esp);
	//ALLTASK[1]->timer = 20;
	//ALLTASK[4]->timer = 40;
	
	myswitch(1);
	while(1);

	row=1; col=4; put_chars(message1,WHITE,&row,&col);
	row++; col=4; put_chars(message2,WHITE,&row,&col);
	row++; col=4; put_chars(message1,WHITE,&row,&col);	

    row_now = 4;col_now = 4;
    
    
    clear_screen();
    row=7; col=4; put_chars(message1,WHITE,&row,&col);
	row++; col=4; put_chars(message3,WHITE,&row,&col);
	row++; col=4; put_chars(message1,WHITE,&row,&col);
    
	return 0;
}




