#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>


/////////////////////////////////////////////////时间戳转日期
void timeStampToDate(uint32_t timeStamp)
{
	struct tm *info;
	uint8_t time[6] = {0};
    info = gmtime(&timeStamp);//时间戳转换为结构体tm

    time[0] = info->tm_year - 100;
    time[1] = info->tm_mon + 1;
    if ((info->tm_hour + 8) > 24)
    {
        time[2] = info->tm_mday + 1;
        time[3] = (info->tm_hour + 8) % 24;
    }
    else
    {
        time[2] = info->tm_mday;
        time[3] = info->tm_hour + 8;
    }
    time[4] = info->tm_min;
    time[5] = info->tm_sec;
    printf("time is :%d.%d.%d.%d:%d:%d", time[0], time[1], time[2], time[3], time[4], time[5]);

    return;
}
////////////////////////////////////////////////////////////////////
typedef unsigned int  uint32_t;
typedef unsigned short     uint16_t;
//////////////////////日期格式转换时间戳
uint16_t time_bcd[6]={2020,8,27,20,20,20};//

static uint16_t mon_yday[2][12] =
{
	{0,31,59,90,120,151,181,212,243,273,304,334},
	{0,31,60,91,121,152,182,213,244,274,305,335},
};
int isleap(int year)
{
	return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}
uint32_t mktimestamp(uint16_t *dt,uint16_t len)
{
	uint32_t result;
    int i =0;
    // 以平年时间计算的秒数
    result = (dt[0] - 1970) * 365 * 24 * 3600 +
    (mon_yday[isleap(dt[0])][dt[1]-1] + dt[2] - 1) * 24 * 3600 +
    dt[3] * 3600 + dt[4] * 60 + dt[5];
    // 加上闰年的秒数
    for(i=1970; i < dt[0]; i++)
    {
      if(isleap(i))
      {
        result += 24 * 3600;
      }
    }
    return result;
}
/////////////////////

int main()
{
    // uint32_t time = mktimestamp(time_bcd,6);
    // printf("timestamp : %d",time);

    timeStampToDate(1617677766);

    getchar();
    return 0;

}

// typedef union{
//  char c;
//  int a;
//  int b;
// }Demo;
 
// int main(int argc, char **argv)
// {
//  Demo d;
//  d.c = 'H';
//  d.a = 10;
//  d.b = 52;
// char cc;

// 	printf("sizecc: %s\n", cc);
//  printf("size: %d\n", sizeof(d));
//  printf("c: %c\t a: %d\t b: %d\n", d.c, d.a, d.b);
// //  getchar();



//  printf("aaaaaaaaaaaaaaaaa");

//  getchar();

//   return 0;
// }
/*
#include <stdio.h>
#include <string.h>

typedef unsigned int  uint32_t;
typedef unsigned short     uint16_t;
//////////////////////日期格式转换时间戳
uint16_t time_bcd[6]={2020,8,27,20,20,20};//

static uint16_t mon_yday[2][12] =
{
	{0,31,59,90,120,151,181,212,243,273,304,334},
	{0,31,60,91,121,152,182,213,244,274,305,335},
};
int isleap(int year)
{
	return (year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0);
}
uint32_t mktimestamp(uint16_t *dt,uint16_t len)
{
	uint32_t result;
    int i =0;
    // 以平年时间计算的秒数
    result = (dt[0] - 1970) * 365 * 24 * 3600 +
    (mon_yday[isleap(dt[0])][dt[1]-1] + dt[2] - 1) * 24 * 3600 +
    dt[3] * 3600 + dt[4] * 60 + dt[5];
    // 加上闰年的秒数
    for(i=1970; i < dt[0]; i++)
    {
      if(isleap(i))
      {
        result += 24 * 3600;
      }
    }
    return result;
}

*/