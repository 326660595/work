#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool test_bool(){
    int a=1;
    // return false;
}
/*
char*strcpy(char *dest, const char *src);

其对字符串进行操作，完成从源字符串到目的字符串的拷贝,当源字符串的大小大于目的字符串的最大存储空间后，执行该操作会出现段错误。

int sprintf(char*str, const char *format, ...)

函数操作的源对象不限于字符串：源对象可以是字符串、也可以是任意基本类型的数据。主要是实现将其他数据类型转换为字符串

void *memcpy(void*dest, const void *src, size_t n)

实现内存的拷贝，实现将一块内存拷贝到另一块内存。该函数对源对象与目的对象没有类型现在，只是对内存的拷贝
*/
int main(){
    char *h = "hellow world";
    int h1[10] = {1,2,3,4,5,5,6};
    int num = 53;
    char a[20];// = malloc(10);
    char a1[20];// = malloc(10);
    // sprintf(a,"%d",num);
    // printf("h is: %s\n",a);

    // char s[10];
    // char* who = "I";
    // char* whom = "CSDN";

    char btest = 0;

    bool atest = test_bool();
    printf("true or false :%d",atest);
    if(atest){
        printf("good");
        putchar(atest);
    }
    
    printf("\n");

    // memcpy(a,h,strlen(h));
    sprintf(a1,h1,strlen(h));//和memcpy达成同样的效果
    printf("a1 is: %s\n",a1);

    // printf("a is: %s\n",a);
    // printf("a is: %p\n",a);
    // printf("a0 is: %p\n",a[0]);
    // printf("a3 is: %p\n",a[3]);
    // printf("a19 is: %p\n",a[18]);
    // free(a);
    // // sprintf(s, "%-8d%8d", 123, 4567);
    // //sprintf(s, "%8x", 4567);
    // int i = 100;
    // //sprintf(s, "%.2f", i);
    // sprintf(s, "%s love %s.", who, whom); //产生："I love CSDN. "

    // //sprintf(s, "%.2f", (double)i);
    // printf("s is: %s\n",s);

    // printf("h is: %#x\n",num);
    getchar();
}

// int main(void)
// {
//    char buffer[80];
//    sprintf(buffer, "An approximation ofPi is %f\n", 20);
//    printf("put \n");
//    puts(buffer);
//    getchar();
//    return 0;
// }

//  int main()
// {
//     char *s="Golden Global View";
//     char d[20];
//     memcpy(d,s,strlen(s));
//     d[strlen(s)]=0;
//     printf("%s",d);

//     getchar();
//     return 0;
// }


