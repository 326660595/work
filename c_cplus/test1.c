#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
/*
1.1格式控制符
%d：用于输出整型数（整型指本质为整型的数，如int、short等）

%c：用于输出一个字符

%s：用于输出一个字符串

%o：以无符号八进制形式输出整数值

%x:以无符号十六进制形式输出整数值

%u:以无符号形式输出十进制数

%f:用来输出浮点数（float），精度为6位小数，第七位四舍五入。

%p：指针的值
*/

typedef unsigned char      uint8_t;
typedef unsigned int       uint32_t;
bool rbool();


int atest(){
    if(rbool()){
        return 1;
    }
    return 0;
}


void ugen_flash_read_state(int *reset_state){
		*reset_state = 99;
}

int main(){

    char *locktype = "1";
    char *userlimit = "1";
    char * id_str = "1";
    

    char* key_str = (char*)malloc(sizeof(char) * 10);
    strcpy(key_str,"|");
    strcat(key_str, locktype);
    strcat(key_str, userlimit);
    strcat(key_str, id_str);
    char *keys_str = (char *)malloc(sizeof(key_str)+1);
    memset(keys_str,0,1);
    strcat(keys_str,key_str);

    printf("| size is :%d",sizeof("|"));
    printf("locktype size is :%d",sizeof("1"));

    printf("key_str is %s\n",key_str);
    printf("keys  is  %s\n",keys_str);


    // char * key = (char *)malloc(sizeof(char)*4);
    // uint8_t locktype = 1;
    // uint8_t userlimit = 2;
    // uint8_t type_limit = (locktype << 4) + userlimit;
    // printf("type_limit is:%x\n",type_limit);

    // // uint8_t type_limit = 23;
    // uint8_t id = 6;

    // snprintf(key, 5, "%02x%02x", type_limit, id);
    // printf("key is:%s\n",key);
    
    // getchar();
    // free(key);




    //双重指针,"*"解引用；”&“取地址；
    // char i = 'h';
    // char *a = &i;
    // char **b = &a;
    // printf("The i is  %p\n",&i);
    // printf("The a is  %p\n",&a);
    // printf("The b is  %p\n",&b);
    // printf("The a is a %p\n",*a);
    // printf("The b is a %p\n",*b);//**b双重指针指向a的地址，*b指向*a所指向的地址；



    // char a[10]={0};
    // char b[10]={"\0"};
    // printf("The a is  %s\n",a);
    // printf("The b is  %s\n",b[0]);
    



        // uint8_t a=10;
        // uint8_t b=20;
        // uint8_t c=a-b;
		// time_t sum_time;
		// sum_time=time(NULL);
        // int a = atest();
        
        // int a = 9;
        // int *reset_state;
        // printf("The reset_state is  %p\n",reset_state);
        // printf("The reset_state+1 is  %p\n",++reset_state);

        // uint8_t *a_32;
        // printf("The a_32 is  %p\n",a_32);
        // printf("The a_32+1 is  %p\n",++a_32);

        // ugen_flash_read_state(&a);
        // printf("The a is  %d\n",a);
		// printf("The number of seconds since January 1, 1970 is  %d\n",366&111);

        getchar();
}

static  bool screen_open = true;//闹钟屏幕开或关
bool rbool(){
    if(screen_open){
        return true;
    }
    return false;
}


