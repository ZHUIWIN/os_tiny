/* create by zhui
 * task.c
 * 2015.7
 */


#include "task.h"

int init_all(){
    int i =0;
    for(i=0;i<MAX_TASK_NUM;i++)
	init_task(i);
}

int init_task(int id){
    int i = 0;
    for(i=0;i<1024;i++) ALLTASK[id]->taskStack[i] = 0;
    ALLTASK[id]->taskStack[1023]= 8;
    ALLTASK[id]->esp = 0;
    ALLTASK[id]->ebp = 0;
    ALLTASK[id]->idle = 0;
    ALLTASK[id]->timer = -1;
    ALLTASK[id]->period = 0;
    ALLTASK[id]->priority= 1;
    ALLTASK[id]->sleeptime = 0;
    ALLTASK[id]->deflag = 0;
    ALLTASK[id]->eflag = 0x0202;
}


void save_task(int id,unsigned long esp,unsigned long ebp,unsigned long eflag){
    ALLTASK[id]->esp = esp;
    ALLTASK[id]->ebp = ebp;
    ALLTASK[id]->eflag = eflag;
}
void create_task(int id,void *func){
     ALLTASK[id]->taskStack[1022]= (unsigned long)func;
     //ALLTASK[id]->taskStack[1021]=0x0202;
     ALLTASK[id]->esp = (unsigned long) &ALLTASK[id]->taskStack[1022];
}


void period(int id,int time){ 
    if(ALLTASK[id]->deflag == 1){ //周期性任务创建
		void *func = (void*)ALLTASK[id]->taskStack[1022];
	    init_task(id);
	    create_task(id,func);
	    ALLTASK[id]->timer = time;
	}
}

void period_wait(){
    
}



int delay(int time){
    ALLTASK[tasknow]->idle =time;
    schedule();
}



int myswitch(int next_id){
    save_temp();
    if(!ALLTASK[tasknow]->deflag){    
        save_task(tasknow,ptr2,ptr3,ptr4);
    }    
    if(ALLTASK[next_id]->esp == 0){
        init_task(next_id);
        
    } //NOT necessary
    
    ptr2 = ALLTASK[next_id]->esp;
    ptr3 = ALLTASK[next_id]->ebp;
    ptr4 = ALLTASK[next_id]->eflag;
    tasknow = next_id;
    goto_temp();
      
    return 0;
}

int destory_task(){
    ALLTASK[tasknow]->esp = 0;
    ALLTASK[tasknow]->ebp = 0;
    ALLTASK[tasknow]->idle = 0;
    ALLTASK[tasknow]->priority=0;
    ALLTASK[tasknow]->deflag = 1;
    schedule();
}

void schedule(){
    int i = 0;
    int ready[MAX_TASK_NUM];
    for(i=1;i<MAX_TASK_NUM;i++){
        ready[i]=0;
        if( ALLTASK[i]->esp !=0 
            && ALLTASK[i]->idle==0 
            && ALLTASK[i]->timer== -1 
            && ALLTASK[i]->sleeptime ==0
            ){
                ready[i]=1;
        }
    }
    
     for(i=1;i<MAX_TASK_NUM;i++){
        if(ALLTASK[i]->sleeptime !=0 ) check_sleep_queue(i);
        else delete_sleep_queue(i);
     }
     
     
     
    //printf("schedu\n");
    
    int max_taskid = 9;//默认idle
    for(i=1;i<9;i++){
        if(ready[i] ){
            if(ALLTASK[i]->priority > 1){
                if(i < max_taskid) max_taskid=i;//id High priority FCFS
            }
            else check_queue(i);
        }
        else delete_queue(i);
    }
    
    if(max_taskid == 9){  //如果没有更高优先级任务，进入时间片轮转，否则优先级掉入
        int tmp = next_RR(); //next RR 
        if(tmp != 0) myswitch(tmp);
        else myswitch(max_taskid);
    }
    else if(max_taskid != tasknow)    myswitch(max_taskid);
 
}


void init_RR_Queue(){
    int i =0;
    for(i=1;i<MAX_TASK_NUM;i++) RR_Queue[i]= 0;
    
}
void delete_queue(int id){
    int i =0,j =0;
    for(j=1;j<MAX_TASK_NUM;j++) 
        if(RR_Queue[j] == id) {
            for(i = j;i<MAX_TASK_NUM;i++){
                if(RR_Queue[i+1] != 0) RR_Queue[i]=RR_Queue[i+1];
                else {
                    RR_Queue[i]=0;
                    break;
                }
            }
            break;
        }
}

void check_queue(int id){
    int i =0,j=0;
    for(i=1;i<MAX_TASK_NUM;i++) 
        if(RR_Queue[i]== id) break;
    if(i==MAX_TASK_NUM){
        for(j=1;j<MAX_TASK_NUM;j++) 
            if(RR_Queue[j] == 0 ){
                RR_Queue[j] = id;
                break;
            }
    }
}

int next_RR(){
    int next = RR_Queue[1],i = 2;
    for(i = 1;i<MAX_TASK_NUM;i++){
        if(RR_Queue[i+1] != 0) RR_Queue[i]=RR_Queue[i+1];
        else {
            RR_Queue[i]=next;
            break;
            }
    }
    
    if(next == 0) return 9;
    return next;
}

void sleep(){
    if(ALLTASK[tasknow]->period != 0)
        ALLTASK[tasknow]->sleeptime = ALLTASK[tasknow]->period;
    else ALLTASK[tasknow]->sleeptime = 0xFFFF;
    schedule();
}

void wakeup(int id){
    ALLTASK[id]->sleeptime=0;
    //schedule();
    myswitch(id);
}

void init_sleep_queue(){
    int i =0;
    for(i=1;i<MAX_TASK_NUM;i++) sleep_queue[i]= 0;
}
void check_sleep_queue(int id){
    int i =0,j=0;
    for(i=1;i<MAX_TASK_NUM;i++) 
        if(sleep_queue[i]== id) break;
    if(i==MAX_TASK_NUM){
        for(j=1;j<MAX_TASK_NUM;j++) 
            if(sleep_queue[j] == 0 ){
                sleep_queue[j] = id;
                break;
            }
    }
}
void delete_sleep_queue(int id){
    int i =0,j =0;
    for(j=1;j<MAX_TASK_NUM;j++) 
        if(sleep_queue[j] == id) {
            for(i = j;i<MAX_TASK_NUM;i++){
                if(sleep_queue[i+1] != 0) 
                    sleep_queue[i]=sleep_queue[i+1];
                else {
                    sleep_queue[i]=0;
                    break;
                }
            }
            break;
        }
}

