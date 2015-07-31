int myTask1(void){
    printf_system("task1\n");
    destory_task();
	char *message1 = "**************************************\0";
	char *message2 = "*        HELLO WORLD Task1!          *\0";
	int row=7,col=0,allrow =1,i=0;
	while(i<10){
	    allrow++; row=allrow%25; col=4; 
	    if(row == 1) clear_screen();
	    put_chars(message1,WHITE,&row,&col);
	    
	    allrow++; row=allrow%25; col=4; put_chars(message2,WHITE,&row,&col);
	    allrow++; row=allrow%25; col=4; put_chars(message1,WHITE,&row,&col);
	    
	    delay(40);i++;
	}
    destory_task();
}

int myTask2(){
    printf_system("task2\n");
    destory_task();
	char *message2 = "*        HELLO WORLD Task2!          *\0";
	int row=7,col=0;
	row=7; col=4; put_chars(message2,WHITE,&row,&col);
	
    int allrow =4;
    int i = 0;
    while(i<20){
	    allrow++; row=allrow%25; col=4; if(row=0) row++;
	    if(row == 1) clear_screen();
	    allrow++; row=allrow%25; col=4; put_chars(message2,WHITE,&row,&col);
	    delay(20);i++;
	 }    
    destory_task();
};

int myTask3(){
    char *message2 = "*        HELLO WORLD Task3333333!          *\0";
	int row=7,col=0;
	row=8; col=4; put_chars(message2,WHITE,&row,&col);
	while(1){
	    row++;row = row%24;
	    put_chars(message2,WHITE,&row,&col);
	    sleep();
	}
	destory_task();
    };
//print PI 1
int a2=10000,b2,c2=44800,d2,e2,f2[44801],g2;
int myTask4(){
    for(;b2-c2;)
        f2[b2++]=a2/5;
    for(;d2=0,g2=c2*2;c2 -=14,printf_system1("%4d",e2+d2/a2),e2=d2%a2)
        for(b2=c2; d2+=f2[b2]*a2,f2[b2]=d2%--g2,d2/=g2--,--b2; d2*=b2);
    
    printf_system1("\n");
    destory_task();
};

//print PI 2
int a=10000,b,c=44800,d,e,f[44801],g;
int myTask5(){    
    for(;b-c;)
        f[b++]=a/5;
    for(;d=0,g=c*2;c -=14,printf_system2("%4d",e+d/a),e=d%a)
        for(b=c; d+=f[b]*a,f[b]=d%--g,d/=g--,--b; d*=b);

    printf_system2("\n");
    destory_task();
};
int myTask7(){printf_system("task7\n"); 
    int i = 2;
    while (i) {     // produce an item
        wait (empty);
        wait (mutex); // add the item to the buffer
        printf_system("producer 1\n");
        signal (mutex);
        signal (full);
        
        i--;
    }
    destory_task();
};

int myTask6(){ printf_system("task6\n"); 
     int i =3000;
    while (i) {
        wait (full);
        wait (mutex);   // remove an item from buffer
        printf_system("            consumer\n");i--;
        
        signal (mutex);
        signal (empty); // consume the removed item
        
    }
    destory_task();
};

int myTask8(){printf_system("task8\n"); 
    int i = 2;
    while (i) {     // produce an item
        wait (empty);
        wait (mutex); // add the item to the buffer
        printf_system("                                producer 2\n");
        signal (mutex);
        signal (full);
        i--;
    }
    destory_task();
};


int idle_task(){
    printf_system("task9\n");
    while(1);
}





