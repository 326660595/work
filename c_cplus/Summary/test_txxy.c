#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#define PROPERTYMAXSIZE 30  //mcu上报指令一次最多能传递的属性和事件个数



typedef struct 
{
    char * name;
    uint8_t * data;
    uint8_t * value;
    
}ugen_config;
///////////////////////////////事件
#define LEAKINGEVENT "leakingEvent"//漏水事件
uint8_t leakingEvent_data[3] = {0x03,0x00,0x04};

#define FAULTREPORTEVENT "faultReportEvent"//故障上报事件
uint8_t faultReportEvent_data[3] = {0x03,0x00,0x05};


////////////////////////////////////

/////////////////////////////////属性
#define POWERSTATE "powerstate"//开关
uint8_t powerstate_data[3] = {0x05,0x00,0x01};

#define ERRORCODE "Errorcode"//错误码
uint8_t Errorcode_data[3] = {0x05,0x00,0x02};


uint8_t value_data[2] = {0x00,0x00};
ugen_config WaterPurifier[] = {
    {LEAKINGEVENT,leakingEvent_data,NULL},
    {POWERSTATE,powerstate_data,value_data},
    {ERRORCODE,Errorcode_data,value_data},
    {FAULTREPORTEVENT,faultReportEvent_data,value_data},
    {NULL,NULL,NULL}

};

//D1 FF 05 01 03 00 04 
//extern user_example_ctx_t *user_example_get_ctx(void);
// int get_ugen_config_value(uint8_t *data,uint8_t len)
// {
//     printf("get_ugen_config_value size_NowConfig:%d\n",sizeof(ugen_config));
//     ugen_config NowConfig[PROPERTYMAXSIZE];
//     int NowConfig_sum = 0;
//     uint8_t msg_len = data[2];
//     uint8_t msg_cmd = data[3];
//     uint8_t property_len = data[4];//单属性或事件长度

//     uint8_t *p = NULL;
//     p = (data + 4);//总循环的指针位置
//     printf("data[4]=%d;; *p =%d\n",property_len,*p);

//     int check_config = 0;
//     int check_1 = (WaterPurifier[check_config].name != NULL)?1:0;
//     printf("msg_len - 1 =%d;;WaterPurifier[check_config].name != NULL =%d;;\n",msg_len - 1,check_1);
//     while(((msg_len - 1) > 0)&(WaterPurifier[check_config].name != NULL))//属性查找完没有或到长度最后结束
//     {
//         printf("WaterPurifier[check_config].name =:%s\n",WaterPurifier[check_config].name);
//         int i = 0;
//         for(i;i<=property_len;)
//         {
//             printf("i_is :%d;;data_len\n",i,sizeof(WaterPurifier[check_config].data));
//             if(i == sizeof(WaterPurifier[check_config].data))
//             {
//                 printf("set pro :%d;;check_config\n",NowConfig_sum,check_config);
//                 NowConfig[NowConfig_sum] = WaterPurifier[check_config];
//                 if(NowConfig[NowConfig_sum].value != NULL)
//                 {
//                     printf("aaaaaaa\n");
//                     NowConfig[NowConfig_sum].value[0] = *(p+i);
//                     NowConfig[NowConfig_sum].value[1] = *(p+i+1);
//                     printf("---%d;;%d;;%s;\n",NowConfig[NowConfig_sum].value[0],NowConfig[NowConfig_sum].value[1],NowConfig[NowConfig_sum].name);
//                 }
//                 printf("set end;\n");
//                 p += property_len;
//                 msg_len -= property_len;
//                 property_len = *p;
//                 NowConfig_sum ++;
                
//                 break;
//             }
//             // if(!(WaterPurifier[check_config].value))
//             // {
//             //     i = 2;
//             //     continue;
//             // }
//             printf("check_config :%d;;\n",check_config);
//             printf("WaterPurifier[check_config].data[i]is :%d\n",WaterPurifier[0].data[0]);
//             int check_in = WaterPurifier[check_config].data[i];
//             printf("good 2,*(p + i) =%d;;check_in =%d\n",*(p + i),check_in);
//             if (check_in == *(p + i))
//             {
//                 printf("good 3\n");
//                 i++;
//             }
//             else
//             {
//                 printf("check end\n");
//                 break;
//             }            
//             printf("good 1\n");
//         }
//         check_config ++;
//         printf("NowConfig_sum =%d",NowConfig_sum);
//     }
//     if(NowConfig_sum == 0)
//     {
//         printf("NowConfig_sum == 0");
//         return 0;
//     }
//     ///////////////////////////
//     // printf("++++++ up the cmd start+++++++++");
//     // user_example_ctx_t *user_example_ctx = user_example_get_ctx();
//     // char *payload = NULL;
//     // cJSON *root;
//     // root = cJSON_CreateObject();//a,b,1 {"a":}
//     // int res = 0;
//     // if(NowConfig[0].value != NULL)//属性
//     // {
//     //     printf("+pro up the cmd start+\n");
//     //     for(int i = 0;i <= NowConfig_sum;i++)
//     //     {
//     //         uint16_t value = (NowConfig[i].value[0]<<8) + NowConfig[i].value[1];
//     //         cJSON_AddNumberToObject(root,NowConfig[i].name,value);
//     //     }
//     //     payload = cJSON_Print(root); 
//     //     printf("+pro up the cmd start2;;%s",payload);
//     //     res = IOT_Linkkit_Report(user_example_ctx->master_devid, ITM_MSG_POST_PROPERTY, (unsigned char *)payload, strlen(payload));//上报      
//     // }
//     // else//事件
//     // {
//     //     printf("++++++event up the cmd start+++++++++");
//     //     char *event_id = NowConfig[0].name;
//     //     for(int i = 1;i <= NowConfig_sum;i++)
//     //     {
//     //         uint16_t value = (NowConfig[i].value[0]<<8) + NowConfig[i].value[1];
//     //         cJSON_AddNumberToObject(root,NowConfig[i].name,value);
//     //     }
//     //     payload = cJSON_Print(root); 
//     //     printf("++++++event up the cmd start2;;%s",payload);
//     //     res = IOT_Linkkit_TriggerEvent(user_example_ctx->master_devid, event_id, strlen(event_id), (unsigned char *)payload, strlen(payload));
//     // }
//     // printf("res is +++++==== %d",res);
//     // cJSON_Delete(root);                                          //释放内存
//     // aos_free(payload);
//     ////////////////////////
//     //return res;
// }
int main(void){

    printf("good\n");
}