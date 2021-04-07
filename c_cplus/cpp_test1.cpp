#include <iostream>

using namespace std;

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
class X{
public:
    int a;
    int b;
    X():a(0),b(0){}//无参构造函数
    X(int a,int b):a(a),b(b){}//有参构造函数，通过函数重载，根据参数自动选择；
};

int main(void)
{
    cout<<"hello world\n";
    X aa1(1,2);
    X aa2;
    X *aa =&aa1;
    aa->a += 100;

    cout<<"aa->a ="<<aa->a<<"  aa2.a="<<aa2.a;

    test_2(&mutex);


    getchar();
}