#include "all.h"
void next_screen(void) {
	int row, col;
	unsigned short *ptr = (unsigned short *)VGA_BASE;
    for(col=0; col< 80; col++) *ptr++;
	for(row=1; row< 25-1; row++) {
	    for (col=0; col< 80; col++)
    		(*ptr++) = *(ptr+80-1);
	}
    for(col=0; col< 80; col++) {
		(*ptr++) =0;
    }
}


void int2char(int p_num,char * tochar){
    int i = 0,j=0,num=0; char tmp[16];
    if(p_num<0) num=-p_num;
    
    for(i=15;i>=0;i--) tmp[i]=-1; 
    i=0;
    while(num>0){
        tmp[i]='0'+num%10;
        num /=10;
        i++;
    }
    for(i=15;i>=0;i--)
        if(tmp[i] != -1) tochar[j++] = tmp[i];
    if( p_num < 0 ) 
        tochar[j++] = '-';
    tochar[j++] = '\0';
}

void printf_system(const char *msg, ...){
    va_list para;				    /* 定义保存函数参数的结构 */  
	int paran_num = 0;			    	/* 纪录参数个数 */  
	char *word;					    /* 存放取出的字符串参数 */  
	char newword[100];
	newword[0]='W';	newword[1]='\0';
	va_start( para, msg );   /* para指向传入的第一个可选参数，  	msg是最后一个确定的参数 */  
    int i = 0,j = 0;char out_char[1000];
    for(i = 0;i<25*80;i++){
        if(msg[i] == '\0') break;
        else if(msg[i] == '%'){
            if(msg[i+1] == 's'){
                word = va_arg( para, char *);
                int k=0;i++;
                while(word[k] != '\0') out_char[j++] = word[k++];
            }
            else if(msg[i+1] == 'd'){
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;
                while(newword[k] != '\0') out_char[j++] = newword[k++];        
            }
            else if(msg[i+2] == 'd'){
                int bits = msg[i+1]-'0';
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;i++;
                while(newword[k] != '\0') k++;
                int q = 0;
                for(q=0;q < bits-k;q++ ) out_char[j++]='0';
                k=0;
                while(newword[k] != '\0') out_char[j++] = newword[k++];
                
            }
            else out_char[j++]= '%';
        }
        else out_char[j++] = msg[i];
    }
    out_char[j++]='\0';
    for(i = 0;out_char[i]!='\0';i++){
        if(col_now == 80) {
            col_now = 0;row_now++;
            if(row_now >= 25) {
                row_now = 24;
                next_screen();
            }
        }
        if(out_char[i] == '\n'){
            col_now = 80;
        }
        else put_char(out_char[i], 0x7,row_now,col_now++);

    }
}

void printf_system1(const char *msg, ...){
    va_list para;				    /* 定义保存函数参数的结构 */  
	int paran_num = 0;			    	/* 纪录参数个数 */  
	char *word;					    /* 存放取出的字符串参数 */  
	char newword[100];
	newword[0]='W';	newword[1]='\0';
	va_start( para, msg );   /* para指向传入的第一个可选参数，  	msg是最后一个确定的参数 */  
    int i = 0,j = 0;char out_char[1000];
    for(i = 0;i<25*80;i++){
        if(msg[i] == '\0') break;
        else if(msg[i] == '%'){
            if(msg[i+1] == 's'){
                word = va_arg( para, char *);
                int k=0;i++;
                while(word[k] != '\0') out_char[j++] = word[k++];
            }
            else if(msg[i+1] == 'd'){
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;
                while(newword[k] != '\0') out_char[j++] = newword[k++];        
            }
            else if(msg[i+2] == 'd'){
                int bits = msg[i+1]-'0';
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;i++;
                while(newword[k] != '\0') k++;
                int q = 0;
                for(q=0;q < bits-k;q++ ) out_char[j++]='0';
                k=0;
                while(newword[k] != '\0') out_char[j++] = newword[k++];
                
            }
            else out_char[j++]= '%';
        }
        else out_char[j++] = msg[i];
    }
    out_char[j++]='\0';
   
    for(i = 0;out_char[i]!='\0';i++){
        if(col_now >= 40) {
            col_now = 0;row_now++;
            if(row_now >= 25) {
                row_now = 24;
                next_screen();
            }
        }
        if(out_char[i] == '\n'){
            col_now = 39;
        }
        else put_char(out_char[i], 0x7,row_now,col_now++);
    }
}


//右半屏输出
void printf_system2(const char *msg, ...){
    va_list para;				    /* 定义保存函数参数的结构 */  
	int paran_num = 0;			    	/* 纪录参数个数 */  
	char *word;					    /* 存放取出的字符串参数 */  
	char newword[100];
	newword[0]='W';	newword[1]='\0';
	va_start( para, msg );   /* para指向传入的第一个可选参数，  	msg是最后一个确定的参数 */  
    int i = 0,j = 0;char out_char[1000];
    for(i = 0;i<25*80;i++){
        if(msg[i] == '\0') break;
        else if(msg[i] == '%'){
            if(msg[i+1] == 's'){
                word = va_arg( para, char *);
                int k=0;i++;
                while(word[k] != '\0') out_char[j++] = word[k++];
            }
            else if(msg[i+1] == 'd'){
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;
                while(newword[k] != '\0') out_char[j++] = newword[k++];        
            }
            else if(msg[i+2] == 'd'){
                int bits = msg[i+1]-'0';
                int num = va_arg( para, int);
                int2char(num,newword);
                int k = 0;i++;i++;
                while(newword[k] != '\0') k++;
                int q = 0;
                for(q=0;q < bits-k;q++ ) out_char[j++]='0';
                k=0;
                while(newword[k] != '\0') 
                    out_char[j++] = newword[k++];
            }
            else out_char[j++]= '%';
        }
        else out_char[j++] = msg[i];
    }
    out_char[j++]='\0';
   
    for(i = 0;out_char[i]!='\0';i++){
        if(col_now == 80) {
            col_now = 41;row_now++;
            if(row_now >= 25) {row_now = 24;next_screen();}
        }
        
        if(out_char[i] == '\n'){
            col_now = 41;
        }
        else put_char(out_char[i], 0x7,row_now,col_now++);
    }
	
    
}
