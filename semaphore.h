#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "memory.h"

typedef struct  {
    int value;
    int process[10];
} semaphore;

semaphore *mutex,*full,*empty;

void new_semaphore(semaphore **S,int);
void de_semaphore(semaphore *S);
void init_semaphore();

int add_process(semaphore *S);
int del_process(semaphore *S);

void wait(semaphore *S);
void signal(semaphore *S);

#endif