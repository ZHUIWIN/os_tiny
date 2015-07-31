# os_tiny

# Readme:
## 最终文档：
>all.c      main.c    myOS.ld   Readme         start16.ld  task.c

>all.h      Makefile  output    semaphore.c    start16.S

>alltask.c  mem.c     printf.c  source2img.sh  start32.S

### all.h  
     一些全局量函数的声明，
### all.c  
     全局量的一些赋值
###alltask.c 
     所有任务函数的实现
### main.c 
    主入口
### makefile
###mem.c 
    内存分配
###myOS.ld
    链接文件
###output
    输出文件夹
###printf.c 
     printf函数实现
###Readme
###semaphore.c
     记录型信号量
###source2img.sh 
    命令行脚本
### start16.S&start16.ld 
    20位实模式
###start32.S 
    32位保护模式
###task.c 
    任务调度相关的函数
