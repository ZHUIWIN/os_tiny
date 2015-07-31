/* create by zhui
 * task.h 
 * 2015.7
 */

#ifndef _TASK_H_
#define _TASK_H_

#define MAX_TASK_NUM 10

extern int tasknow;
extern unsigned long ptr2;
extern unsigned long ptr3;
extern unsigned long ptr4;

struct task_struct
{
    unsigned long esp;
    unsigned long ebp;
    unsigned long idle;
    unsigned long eflag;
    long period;
    long timer;
    long usedtimer;
    long sleeptime;  
    unsigned long priority;
    unsigned long deflag;
    unsigned long taskStack[1024];
}tsk_str;

struct task_struct *ALLTASK[MAX_TASK_NUM];

int init_all();
int init_task(int);
int destory_task();
void create_task(int id,void *func);
void save_task(int id,unsigned long esp,unsigned long ebp,unsigned long eflag);

int delay(int);
int myswitch(int);
void schedule();
void period(int,int);
void period_wait();



/*for the Round robin Algorithm*/
int RR_Queue[MAX_TASK_NUM];
void init_RR_Queue();
void check_queue(int);
void delete_queue(int);
int next_RR();

/*the Sleep Queue*/
int sleep_queue[MAX_TASK_NUM];
void sleep();
void wakeup(int);
void init_sleep_queue();
void check_sleep_queue(int);
void delete_sleep_queue(int);


#endif
