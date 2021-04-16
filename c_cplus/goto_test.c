#include <stdio.h>
#include <time.h>
#include "stl/cJSON.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//#include <queue.h>
#include "test_1.h"
// #include <pthread.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

// int main()
// {
//     printf("good \n");
//     char *a = "hellllo";
//     char *b=(char *)malloc(20);

//     snprintf(b,"%s","a");
//     printf("a is %s",b);

//     getchar();
// }
uint8_t bytes[5] = {0xaa, 0x12, 0x02, 0x06, 0xc4};
uint8_t by2[21] = {0xAA, 0x00, 0x12, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x08, 0x07, 0x01, 0x00, 0x00, 0x00, 0xbc};
int trans(uint8_t *bytes, uint8_t length)
{
    uint32_t checksum = 0x00;
    uint8_t buffer[30];
    for (int i = 0; i < length; i++)
    {
        buffer[i] = bytes[i] & 0xff;
        if (i < length - 1)
            checksum += buffer[i];
    }
    checksum &= 0xff;
    return checksum;
}

uint8_t testtg7100b[13] = {0xFF, 0x00, 0x00, 0x08, 0xD4, 0xA8, 0x01, 0x01, 0x12, 0x02, 0x9e, 0x00, 0x53};
uint32_t trans_check(uint8_t *p_data, uint8_t len)
{

    uint32_t checksum = 0x00;
    printf("checksum is %d \n", checksum);
    checksum += p_data[2];
    checksum += p_data[3];
    int len1 = p_data[3];
    int index = 0;
    while (index < len1)
    {
        checksum += p_data[4 + index];
        index++;
    }
    checksum = checksum & 0xff;
    printf("checksum is %02x \n", checksum);
    return checksum;
}
uint8_t check_data[15] = {0xE5, 0x55, 0x11, 0x12, 0x01, 0x07, 0x20, 0x01, 0x2a, 0x50, 0x00, 0xb2, 0xb3, 0x09, 0x23};
uint8_t check_data1[15] = {0xE5, 0x55, 0x11, 0x21, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD8};
uint8_t check_sum(void *data, uint8_t len)
{
    int i = 0;
    uint8_t sum_byte = 0x00;
    uint8_t uart_send[50] = {'\0'};
    memcpy(uart_send, data, len);
    for (i = 3; i < 14; i++)
    {
        sum_byte += uart_send[i];
    }
    sum_byte = ~sum_byte;
    // sum_byte = sum_byte;
    printf("check_sum: sum = 0x%x", sum_byte);
    return sum_byte;
}

char *ugen_get_version(void)
{
    printf("lllll--%s\r\n", __func__);
    char *myver = "app-1.6.6_v0.0.1-20210203.022203";
    printf("ugen_get_version--->>%s\n", myver);
    char *version = NULL;

    char *p = myver;

    static char buf[80];

    uint8_t count = 0;
    int i = 0;
    while (*p != '-')
    {
        //sprintf(buf,"%s",myver);
        i++;
        p++;
    }

    printf(" i is %d ;;\n", i);
    snprintf(buf, i, "%s", myver);

    //pirntf("=== %s\n ",(char *)buf);

    version = (char *)buf;

    //sprintf(version,"31 %s","a");
    printf("the cmd is a:%s\n", version);
    return version;
}
//////////////////////////

////////////////////////////////////

/////////////////////////////////属性

#define PROPERTYMAXSIZE 30 //mcu上报指令一次最多能传递的属性和事件个数

typedef struct
{
    char *name;
    uint8_t *data;
    uint8_t *value;

} ugen_config;

///////////////////////////////事件
#define LEAKINGEVENT "leakingEvent" //漏水事件
uint8_t leakingEvent_data[3] = {0x03, 0x00, 0x04};

#define FAULTREPORTEVENT "leakingEvent" //故障上报事件
uint8_t faultReportEvent_data[3] = {0x03, 0x00, 0x05};

#define POWERSTATE "powerstate" //开关
uint8_t powerstate_data[3] = {0x03, 0x00, 0x01};

#define ERRORCODE "Errorcode" //错误码
uint8_t Errorcode_data[3] = {0x03, 0x00, 0x01};

uint8_t value_data[2] = {0x00, 0x00};

ugen_config WaterPurifier1 = {LEAKINGEVENT, leakingEvent_data, value_data};

ugen_config WaterPurifier[] =
    {
        {LEAKINGEVENT, leakingEvent_data, value_data},
        {POWERSTATE, powerstate_data, value_data},
        {ERRORCODE, Errorcode_data, value_data},
        {FAULTREPORTEVENT, faultReportEvent_data, value_data},
        {NULL, NULL, NULL}

};

void Spker(char *arr, unsigned char arr_Len)
{
    char Head[] = {0x5A, 0x02, 0x01, 0x02, 0xC0, 0x00, 0x00};
    //char Head[] ="nihaoya";
    char *CRC16_Data;
    int Data_Len = 0, CRC16 = 0;
    arr_Len -= 1;
    Data_Len = arr_Len + 2;

    CRC16_Data = (char *)malloc(100);
    if (CRC16_Data != NULL)
    {
        memset(CRC16_Data, 0, 100);
        memcpy(CRC16_Data, Head, sizeof(Head));
        printf("data=%d", *CRC16_Data);
        //SendDatas((unsigned char *)CRC16_Data, 7);
        //SendDatas(Head, 7);
    }
    else
    {
        printf("\r\n ERROR!!");
    }

    // SendDatas(CRC16_Data, 7);

    free(CRC16_Data);
}
typedef enum
{
    CIPHER_TYPE_NONE = 0,
    CIPHER_TYPE_SELF = 1
} Cipher_Type_e;

int mmmmsss(Cipher_Type_e a)
{
    printf("Cipher_Type_e\n");
}

// int p(a,b){
//     printf("a+b=%d\n",a+b);
//     return 110;
// }
#define check_big(a, b) ((a > b) ? a : b)
struct goto_test
{
    /* data */
    int a;
    double b;
};
char test_char[] = {1, 2, 3, 4};
const void *test_void = test_char;
#define W
#define A
#define B
void ta(int a, int b)
{
    printf("a+b=%d", a + b);
}
void tb(int a, int b)
{
    printf("a*b=%d", a * b);
}
typedef void (*testFuncP)(int a, int b);

testFuncP test_2 = ta;
testFuncP get_testFuncP(void)
{
    return test_2;
}
#define ppf              \
    {                    \
        printf("aaa\n"); \
        printf("bbb\n"); \
    }

#define log_debug(lfmt, ...) printf(lfmt, ##__VA_ARGS__) //宏定义printf，方便注释

int strcmp(const char *s1, const char *s2)
{
    const unsigned char *c1 = (const unsigned char *)s1;
    const unsigned char *c2 = (const unsigned char *)s2;
    unsigned char ch;
    int d = 0;

    while (1)
    {
        d = (int)(ch = *c1++) - (int)*c2++;
        printf("at=%d,bt=%d\n", (int)(ch = *c1++), (int)*c2++);
        if (d || !ch)
            break;
    }

    return d;
}
typedef enum
{
    SOFT_AP, /* Act as an access point, and other station can connect, 4
                stations Max */
    STATION  /* Act as a station which can connect to an access point */
} hal_wifi_type_t;

enum
{
    DHCP_DISABLE = 0,
    DHCP_CLIENT,
    DHCP_SERVER,
};
typedef struct klist_s {
    struct klist_s *next;
    struct klist_s *prev;
} klist_t;// klist_t结构体含有两个成员，是klist_s结构体指针


extern int b;
static int a =990;

int main()
{
    printf("good \n");


    //int b =880;
    printf("a= %d;  b =%d",a,b);




///////////////////////////////////////////////////-----------------------------------------------------
    // hal_wifi_type_t hal1 = SOFT_AP;


    // char *s1 = "aabbc";
    // char *s2 = "aabbdd";
    // if ((-1))
    //     printf("s1-s2=%d\n", strcmp(s1, s2));
    // else
    //     printf("!(-1)=%d\n", !(-1));
    // int w1 = -1;
    // do
    // {
    //     printf("%d is true\n",w1);
    // } while (w1++);

    //////////////////////////------------------------------------------------------
    // uint8_t aa = 8;

    // printf("0-8 = %d\n / \n0-aa = %d\n",0-8,aa = 0-aa);

    // ppf

    // log_debug("abcd = %d\n",100);

    ////////////////////////////------------------------------------------------

    // testFuncP test_a = ta;
    // ta(1,8);

    // printf("test 2\n\n");
    // testFuncP test_3 = get_testFuncP();

    // test_3 = tb;

    // if(test_3){
    //     printf("test 3 good\n\n");
    //     test_3(6,6);
    // }else{
    //     printf("test 3 NULL\n\n");
    // }

    ////////////////////////////-----------------------------------------

    // printf("lll=%d\n", strlen((char *)test_void));

    // int a = 9;
    // int *b = &a;

    // printf("&b=%d", *(&b));

    ///////////////////////////------------------------
    // struct goto_test aabb;
    // aabb.a=99;aabb.b=100;
    // printf("aabb= %d;%d\n\n",aabb.a,aabb.b);
    // printf("good =%d\n",check_big(1,2));
    ////////////////////////////////-------------------------------------
    // printf("size =%d\n",sizeof(uint8_t));
    // Cipher_Type_e aab = CIPHER_TYPE_SELF;
    // mmmmsss(aab);

    // #if defined(W)
    //     printf("\n1");
    // #endif
    // #if defined(A)
    //     printf("\n2");
    // #endif
    // #if defined(B)
    //     printf("\n3");
    // #endif

    // int g_cipher_type = 255;

    // g_cipher_type = (g_cipher_type)? 1:0;
    // printf("g_cipher_type=%d\n",g_cipher_type);

    // char *a=" ";
    //     // ugen_get_version();
    //     // bool test = false;
    //     // test = ((-1) == (0 ? 0 : -1));
    //     // printf("bool = %d\n",test);
    //     // printf("sesult=%d",(-1) == (0 ? 0 : -1));
    // Spker("char *arr", 5);

    //////////////////////////////-----------------------------------
    // const char * str = "1615172877123";
    // int i =100;
    // printf("ss=%s",str);
    // char str1[] = "111111111112222222";
    // while(i)
    // {
    //     i--;
    //     char *p_char = (char *)malloc(sizeof(char) *10);
    //     strncpy(p_char,str,10);
    //     printf("p_char=%s\n",p_char);
    //     free(p_char);

    //     char *p_char2 = (char *)malloc(sizeof(char) *10);
    //     snprintf(p_char2,10,"%s",str);
    //     printf("p_char2=%s\n",p_char2);
    //     free(p_char);
    // }

    //////////////////////////////////------------------------------------

    // uint64_t ntp_time_ms = (uint64_t) strtoll(str, NULL, 10);
    // printf("ms =%d\n",(uint32_t)(ntp_time_ms/1000));
    // char * number = " 12345678901234";
    // char * number_a = (char *)malloc(sizeof(char) * 11);
    // snprintf(number_a,11,"%s",number);
    // printf("number_a = %s\n",number_a);
    // uint64_t num = atol(number_a);

    // printf("num = %d\n",(uint32_t)num);

    ////////////------------------------------------------------------------
    // uint8_t time = 0x50;

    // printf("value is hour= %d ; min =%d\n",(time>>3),(time&0x07));

    ////////////////////---------------------------------
    //     ugen_config *aaa = &WaterPurifier1;

    // printf("%s\n",(*aaa).name);

    //     uint16_t ca = 259;
    //     uint8_t *ca1 = (uint8_t *)&ca;

    //     printf("fffff");
    //     // printf("%d\n",*ca1);
    //     uint8_t caa[5] = {0};
    //     memcpy(caa,&ca,2);

    //     //caa[3] = (uint8_t*)ca;

    //     printf("caa=0x%02x,0x%02x \n",caa[0],caa[1]);

    ////////////////////////////////////------------------------
    // char *at = "99";
    // uint8_t *ab =(uint8_t*)at;

    // printf("ssss=%s\n",ab);

    // printf("abbb;;%d;;%d;\n",ab[0],ab[1]);
    // uint8_t att[20];
    // //snprintf(att,20,"%d",at);
    // memcpy(att,ab,2);
    // printf("%d;;%s\n",att[0],att);

    // char valuestr[30];
    // printf("TYPE_STRING :");
    // for(int i = 0;i < 1;i++)
    // {
    //     //valuestr[i] = Now_value[i];
    //     snprintf(valuestr+i,1,"%d",value_data[i]);
    //     printf("%d",value_data[i]);
    // }
    // printf("\nTYPE_STRING %s:",(char *)valuestr);

    /////////////-----------------------------------------------
    //printf("bbc =%d\n",bbc);
    //     uint8_t abc[5] = {0x00,0x01};
    //     uint8_t * acd = (uint8_t *)malloc(sizeof(uint8_t) * 3);
    //     memcpy(acd,abc,3);
    //     //snprintf(acd,2,"%s","122");

    //     //acd = (uint8_t *)abc;
    //     printf("-a =%d,,sizeof(acb)=%d\n",acd[1],sizeof(abc));
    // free(acd);
    //     uint8_t *p = NULL;
    //     p = (Errorcode_data + 2);//总循环的指针位置

    //     printf("*p =%d\n",*(p-2));

    //     printf("a --->%s\n",WaterPurifier[0].name);
    //     printf("a --->%d\n",WaterPurifier[0].data[1]);

    //////////////////////------------------
    // uint8_t aab[10];
    // aab[0] = 0;
    // aab[1] = 0;
    // aab[2] = 0;
    // aab[3] = 3;
    // if(!NULL){
    //     printf("size aab = %d;;aab=%d;;aab[3]=%d;;abb4 = %d\n",sizeof(aab),aab[0],aab[3],aab[4]);
    // }

    /////////////////////---------------------------------------

    //char sysversion[64];

    //printf("\n33-- %s\n",ugen_get_version());

    //printf("------------");
    //sprintf(sysversion,"",)
    // sprintf(sysversion,"31 %s","a");
    // char * cc = (char *)sysversion;
    // printf("--%s\n",sysversion);
    // printf("cc--%s",cc);

    // sprintf(sysversion,"2");
    //printf("33-- %s\n",ugen_get_version());

    /////////------------------------------
    // int b = check_sum(check_data,15);
    // printf("\ncheck_sum = %d\n",b);
    // int c = 255 - b;
    // printf("\nc = %d\n",c);

    //-----------------------------------------
    // bool ble_switch = false;
    // ble_switch = !ble_switch;
    // uint32_t ad = 0xff9902;
    // uint8_t ax = ad;

    // printf("ax is : %d\n",ble_switch);

    //---------------------------
    // uint8_t payload[16]={0xFF,0x00,0x00,0x08,0xD4,0xA8,0x01,0x01,0x12,0x02,0x09,0x00,0x34,0x09,0x00,0x34};
    // char *a = (char *)malloc(sizeof(char )*20);

    // snprintf(a,"%s",payload);
    // printf("this is :%s",a);

    //----------------
    // char *a = (char *)malloc(sizeof(char)*10);

    // printf("checksum is --->%2x",trans_check(testtg7100b,9));

    // free(a);
    //----------

    // goto A;

    //     char *b = (char *)malloc(sizeof(char)*10);
    //     free(a);free(b);

    // A:
    //     free(a);

    //     printf("yes \n");

    getchar();
}