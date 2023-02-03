//20broF False
extern void abort(void);
void reach_error(){}

#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void __VERIFIER_assert(int expression) { if (!expression) { ERROR: {reach_error();abort();}}; return; }

int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10;

int b1, b2, b3, b4, b5;

int c1, c2, c3, c4, c5;

void *thread1(void * arg)
{
    a1 = 1;
    return 0;
}

void *thread2(void *arg)
{
    a2 = a1;
    return 0;
}

void *thread3(void *arg)
{
    a3 = a2;
    return 0;
}

void *thread4(void *arg)
{
    a4 = a3;
    return 0;
}

void *thread5(void *arg)
{
    a5 = a4;
    return 0;
}

void *thread6(void * arg)
{
    a6 = a5;
    return 0;
}

void *thread7(void *arg)
{
    a7 = a6;
    return 0;
}

void *thread8(void *arg)
{
    a8 = a7;
    return 0;
}

void *thread9(void *arg)
{
    a9 = a8;
    return 0;
}

void *thread10(void *arg)
{
    a10 = a9;
    return 0;
}

void *thread11(void * arg)
{
    b1 = 1;
    return 0;
}

void *thread12(void *arg)
{
    b2 = b1;
    return 0;
}

void *thread13(void *arg)
{
    b3 = b2;
    return 0;
}

void *thread14(void *arg)
{
    b4 = b3;
    return 0;
}

void *thread15(void *arg)
{
    b5 = b4;
    return 0;
}

void *thread16(void * arg)
{
    c1 = 1;
    return 0;
}

void *thread17(void *arg)
{
    c2 = c1;
    return 0;
}

void *thread18(void *arg)
{
    c3 = c2;
    return 0;
}

void *thread19(void *arg)
{
    c4 = c3;
    return 0;
}

void *thread20(void *arg)
{
    c5 = c4;
    return 0;
}

int main()
{
    pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    pthread_t t11, t12, t13, t14, t15, t16, t17, t18, t19, t20;


    pthread_create(&t1, 0, thread1, 0);
    pthread_create(&t2, 0, thread2, 0);
    pthread_create(&t3, 0, thread3, 0);
    pthread_create(&t4, 0, thread4, 0);
    pthread_create(&t5, 0, thread5, 0);
    pthread_create(&t6, 0, thread6, 0);
    pthread_create(&t7, 0, thread7, 0);
    pthread_create(&t8, 0, thread8, 0);
    pthread_create(&t9, 0, thread9, 0);
    pthread_create(&t10, 0, thread10, 0);
    pthread_create(&t11, 0, thread11, 0);
    pthread_create(&t12, 0, thread12, 0);
    pthread_create(&t13, 0, thread13, 0);
    pthread_create(&t14, 0, thread14, 0);
    pthread_create(&t15, 0, thread15, 0);
    pthread_create(&t16, 0, thread16, 0);
    pthread_create(&t17, 0, thread17, 0);
    pthread_create(&t18, 0, thread18, 0);
    pthread_create(&t19, 0, thread19, 0);
    pthread_create(&t20, 0, thread20, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
    pthread_join(t4, 0);
    pthread_join(t5, 0);
    pthread_join(t6, 0);
    pthread_join(t7, 0);
    pthread_join(t8, 0);
    pthread_join(t9, 0);
    pthread_join(t10, 0);
    pthread_join(t11, 0);
    pthread_join(t12, 0);
    pthread_join(t13, 0);
    pthread_join(t14, 0);
    pthread_join(t15, 0);
    pthread_join(t16, 0);
    pthread_join(t17, 0);
    pthread_join(t18, 0);
    pthread_join(t19, 0);
    pthread_join(t20, 0);

    __VERIFIER_assert( !(a1&&a2&&a3&&a4&&a5&&a6&&a7&&a8&&a9&&a10));

    return 0;
}

