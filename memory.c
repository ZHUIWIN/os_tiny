/* create by zhui
 * memory.c 
 * 2015.7
 */

#include "memory.h"

void *  linklistmymalloc(){
    mem_alloced * newlist = listaddr;
    listaddr += sizeof(mem_alloced);
    newlist->start_addr =  0;
    newlist->size = 0;
    newlist->next = 0;
    return newlist;
}


void linklist_init(){
    using_firstlist = linklistmymalloc();
    unuse_firstlist = linklistmymalloc();
    using_lastlist = linklistmymalloc();
    unuse_lastlist = linklistmymalloc();
}

void delete_list(int type,mem_alloced * de_list){
    mem_alloced * next1,*next2;
    if(type == 0){ //using_list delete
        next1 = using_firstlist;
        next2 = using_firstlist;
    }
    if(type == 1){ //unuse_list delete
        next1 = unuse_firstlist;
        next2 = unuse_firstlist;
    }
    while(next1 != 0){
        if(next1 == de_list){
              next2->next = next1->next;
              break;
        }
        else{    
            next2 = next1;
            next1 = (mem_alloced * )next1->next;
        }
    }
    
}


void * mem_manage(int needsize){
    mem_alloced * templist;
    void * alloc =0;
    
    templist = unuse_firstlist;
    while(templist != 0){ 
        if(templist->size == needsize){
            alloc = templist->start_addr;
            delete_list(1,templist);    //从unuse 中删除，malloc中会加入using
            break;
        }
        else if(templist->size > needsize){
            alloc = templist->start_addr;
            templist->size -= needsize;
            templist->start_addr += needsize; //更新unuse块，只用了一部分
            break;
        }
        else templist = (mem_alloced * )templist->next;
    }
    return alloc;
}


void * mymalloc(int size){
    mem_alloced * newlist = linklistmymalloc();
    newlist->start_addr =(int*) mem_manage(size);
    newlist->size = size;
    newlist->next = 0;
    if(using_lastlist->start_addr == 0){
        using_lastlist = using_firstlist=newlist;
    }
    else{
        using_lastlist->next = (struct mem_alloced * )newlist;
        using_lastlist = newlist;
    }
    return newlist->start_addr;
}

int init_mem(){
    if(!mem_init(MEM,20000)) return -1;
    linklist_init();
    unuse_firstlist->start_addr = MEM+5000;
    unuse_firstlist->size = 20000-5000;
    unuse_firstlist->next = 0;
    unuse_lastlist = unuse_firstlist;
}


void * free_system(void *addr){
    mem_alloced * templist = using_firstlist;
    while(templist != 0){
          if(templist->start_addr == addr){
                delete_list(0,templist);//从using总去掉，加入unuse，可以供再次分配，应该插到最前
                mem_alloced * newlist = templist;
                newlist->next = 0;
                if(unuse_firstlist->start_addr == 0){
                    unuse_lastlist = unuse_firstlist= newlist;
                }
                else{
                    newlist->next = (struct  mem_alloced * )unuse_firstlist;
                    unuse_firstlist = newlist;
                }
                break;
          }
          else templist=(mem_alloced * ) templist->next;
    }
}

void gather(mem_alloced * list){
}


int mem_init(int *mem,int size){
    int  i = 0;
    for(i=0;i<size;i++) 
        mem[i]=0x55;
    for(i=0;i<size;i++){ 
        if(mem[i]==0x55)
            mem[i]=0xaa;
        else return i;
    }
    for(i=0;i<size;i++){ 
        if(mem[i] != 0xaa) return i;
    }
    for(i=0;i<size;i++)  mem[i]=0;
    return -1;
}

void * alloc_fixed(int size){
    int tmp = 0;
    if( (tmp = mem_manage_fixed()) != -1)
    ALL[tmp].available = 0;
    return ALL[tmp].start_addr;
}



void free_fixed(void * deleteMem){
    int i = 0;
    for(i = 0;i<10;i++){
        if(ALL[i].start_addr == deleteMem){
             ALL[i].available = 1;
             break;
        }  
    }
}

//声明，


//fixed sized 固定块大小
void init_mem_fixed(){
    mem_init(MEM,20000);
    void * Mem_Start = MEM + 10*sizeof(*ALL) + 1000;
    int i = 0;
    for(i = 0;i<10;i++){
        ALL[i].blocksize = 1500;//块大小
        ALL[i].available = 1;
        ALL[i].start_addr = Mem_Start+1500*i;
        ALL[i].end_addr = Mem_Start+1500*(i+1)-1;
    }
}

int mem_manage_fixed(){
    int i = 0;
    for(i = 0;i<10;i++){
        if(ALL[i].available == 1)
            return i;
    }
    return -1;
}

void create(){
    int i =0;
    int * a = alloc_fixed(100);
    for(i = 0;i<100;i++) a[i]=i;
}


#ifdef _MEM_TEST_
main(){
    int i = 0;
    for(i=0;i<20000;i++) MEM[i]=0;
    init_mem_fixed();
    create();
}
#endif


