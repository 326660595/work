#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// #include <pthread.h>
//#include <threads.h>

uint16_t check_sum(uint8_t *data ,uint32_t len)
{
    if( (data == NULL) || (len == 0)) 
        return NULL;
    uint16_t sum = 0xbeaf;
    for(uint8_t i=0;i<len;i++)
    {
        if (i!=4 && i!=5)
        {
            sum += data[i];
        }
    }
    printf("check_sum: 0x%04x\n",sum);
    return sum;
}
/*LRC校验*/
uint16_t check_sum_lrc(uint8_t *data, uint8_t len)
{
    if( (data == NULL) || (len == 0)) 
        return NULL;
    uint8_t sum = 0x00;
    for(uint8_t i=3;i<len;i++)
    {
        sum += data[i];
    }
    sum = 0x100 - (sum % 0x100);
	printf("check_sum: sum = 0x%x",sum);
    return sum;
}
uint8_t prov_reply[16] = {0xA5, 0xA5, 0x5A, 0x5A, 0xA0, 0xC1, 0xEC, 0x03, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t check_state[12] = {0xA5, 0xA5, 0x5A, 0x5A, 0xBA, 0xC0, 0x01, 0x0B, 0x00, 0x00, 0x01, 0x00};
//uint8_t reset_reply[12] = {0xA5, 0xA5, 0x5A, 0x5A, 0x99, 0xC1, 0xE9, 0x03, 0x00, 0x00, 0x01, 0x00};
uint8_t reset_reply[44] = {0xD1,0x68,0x41,0x12,0x04,0x00,0x05,0x03,0x05,0x00,0x03,0x00,0x09,0x04,0x00,0x02,
                            0x00,0x04,0x00,0x02,0x01,0x05,0x00,0x04,0x00,0x09,0x05,0x00,0x06,0x00,0x0A,0x05,
                            0x00,0x07,0x00,0x0A,0x04,0x00,0x0B,0x00,0x04,0x00,0x0C,0x00};
uint8_t aabb[17] = {0xD1,0xCB,0x0E,0x12,0x04,0x00,0x05,0x03,0x05,0x00,0x03,0x00,0x09,0x04,0x00,0x02,0x00};
bool lengthCompare(int a, int b)  //原函数
{
    printf("ptr--star  a=%d,b=%d\n",a,b);
    return true;
}
typedef bool (*pf)(int a, int b);   //指向函数lengthCompare的指针,未初始化
bool (*pd)(int a, int b);

char * name = "xiaoming12345";
void test_cs(char *a)
{
    
    memcpy(a,name,8);
    
}

int thr_fun(void *);

    

int main(void)
{
    printf("hello world\n");

    // thrd_t thr;
    // int ret; //保存thrd_create函数的返回值用于判断线程是否创建成功：0为成功，1为失败。
    // ret = thrd_create(&thr, thr_fun, NULL); //将thr_fun函数放在一个新的线程中执行
    // if (ret != thrd_success) {
    //     printf("error!!!\n");
    //     getchar();
    //     exit(-1);
    // }









///////////////////////////--------------------------------------
    // char ap[] = "123xiaoming";
    // //ap = name;
    // test_cs(ap);
    // printf("yes =%s\n",ap);
    // char p[] = "hhh";

    // *(p+1) = 'a';
    // //char a[] = {0};

    // printf("yes =%s\n",p);

    // check_sum_lrc(reset_reply,sizeof(reset_reply));
    // check_sum_lrc(aabb,17);

    ////////////////////--------------------
    // check_sum(prov_reply,16);

    // pf a = lengthCompare;
    // a(1,2);

    // pd = lengthCompare;
    // pd(2,3);

    getchar();

}