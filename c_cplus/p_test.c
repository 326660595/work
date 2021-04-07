#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//任何声明变量的语句前面加上typedef之后，原来是变量的都变成一种类型。不管这个声明中的标识符号出现在中间还是最后.
typedef int mbedtls_threading_mutex_t;

typedef void (*test_p)(int *a); //typedef定义test_p为一个函数指针的类型名，该函数指针指向一个返回void,形参为int* 的函数；
typedef int f();                // 定义一个名为f, 参数为空, 返回值为int的函数类型

void threading_mutex_dummy(mbedtls_threading_mutex_t *int_l)
{
    printf("good ;int_l =%d\n", *int_l);
}
void (*mbedtls_mutex_init)(mbedtls_threading_mutex_t *) = threading_mutex_dummy; //函数指针 mbedtls_mutex_init 指向一个返回void,形参为mbedtls_threading_mutex_t * 的函数；


/////////////////////////////////////////-----------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    int mutex;
    char is_valid;
} mbedtls_threading;
mbedtls_threading mutex = {88,'a'};


void test_2(mbedtls_threading *mutex)
{
    printf("\nmtex =%d,valid =%c\n",mutex->mutex,mutex->is_valid);

}


#ifdef __cplusplus
}
#endif
/////////////////////////////////////////-----------------------------------------

int main(void)
{
    int a = 3;
    mbedtls_mutex_init(&a);
    test_p p_a = threading_mutex_dummy;
    p_a(&a);

    test_2(&mutex);

    getchar();
}