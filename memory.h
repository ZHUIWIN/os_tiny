#ifndef _MEM_H_
#define _MEM_H_

struct memory{
    int available;
    int blocksize;
    void * start_addr;
    void * end_addr;
};
struct memory ALL[10];


typedef struct Mem_alloced{
    int * start_addr;
    int  size;
    struct mem_alloced * next;
} mem_alloced;

extern int tasknow;

mem_alloced * using_firstlist;
mem_alloced * unuse_firstlist;
mem_alloced * using_lastlist;
mem_alloced * unuse_lastlist;

void *  linklistmymalloc();
void linklist_init();
void delete_list(int type,mem_alloced * de_list);
void * mem_manage(int needsize);
void * mymalloc(int size);
int init_mem();
void * free_system(void *addr);
void gather(mem_alloced * list);
int mem_init(int *mem,int size);

void * alloc_fixed(int size);
void free_fixed(void * deleteMem);
void init_mem_fixed();
int mem_manage_fixed();
void create();

#ifdef _MEM_TEST_
    #include <stdio.h>
    int MEM[20000];
    void * listaddr=MEM+5000;
#endif


#ifndef _MEM_TEST_
    extern _end;
    int *MEM;
    void * listaddr;
#endif





#endif