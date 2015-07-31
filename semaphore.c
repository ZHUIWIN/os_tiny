/* create by zhui
 * semaphore.c
 * 2015.7
 */

#include "semaphore.h"

void new_semaphore(semaphore **S,int value){
    (*S) = (semaphore *)mymalloc(sizeof(semaphore)/sizeof(int)+1);
    (*S)->value = value;
    int i = 0;
    for(i = 0; i < 10;i++){
        (*S)->process[i] = 0;
    }
}

void de_semaphore(semaphore *S){
    free_system(S);
}

void init_semaphore(){
    new_semaphore(&mutex,1);
    new_semaphore(&full,0);
    new_semaphore(&empty,5);
}


int add_process(semaphore *S){ 
    int i = 0;
    for(i = 0; i < 10;i++){
        if(S->process[i] == 0) {
            S->process[i]=tasknow;
            break;
        }
    }
    if(i==10 && S->process[i] != 0)
        return -1;
    return  0;
}

int del_process(semaphore *S){
    int i = 0,tmp= 0;
    if(S->process[0] != 0) 
        tmp = S->process[0];
    for(i = 0; i < 9;i++){
        S->process[i] = S->process[i+1];
    }
    S->process[9] = 0;
    return tmp;
}

//提供信号量的创建、句柄获取、wait、signal、销毁接口

void wait(semaphore *S){
    S->value--;
    if (S->value<0){
        add_process(S);
        sleep();
    }
}
void signal(semaphore *S){
    S->value++;
    if (S->value <= 0){
        int P =  del_process(S);
        wakeup(P);
    }
}
