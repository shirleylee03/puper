//30bro True
extern void abort(void);
void reach_error(){}

#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void __VERIFIER_assert(int expression) { if (!expression) { ERROR: {reach_error();abort();}}; return; }

int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
int b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;
int c1,c2,c3,c4,c5,c6,c7,c8,c9,c10;

void *thread1(void * arg)
{
    a1=1;
    return 0;
}

void *thread2(void *arg)
{
    a2=1;
    return 0;
}

void *thread3(void *arg)
{
    a3=1;
    return 0;
}

void *thread4(void *arg)
{
    a4=1;
    return 0;
}

void *thread5(void *arg)
{
    a5=1;
    return 0;
}

void *thread6(void * arg)
{
    a6=1;
    return 0;
}

void *thread7(void *arg)
{
    a7=1;
    return 0;
}

void *thread8(void *arg)
{
    a8=1;
    return 0;
}

void *thread9(void *arg)
{
    a9=1;
    return 0;
}

void *thread10(void *arg)
{
    a10=1;
    return 0;
}

void *thread11(void * arg)
{
    b1=1;
    return 0;
}

void *thread12(void *arg)
{
    b2=1;
    return 0;
}

void *thread13(void *arg)
{
    b3=1;
    return 0;
}

void *thread14(void *arg)
{
    b4=1;
    return 0;
}

void *thread15(void *arg)
{
    b5=1;
    return 0;
}

void *thread16(void * arg)
{
    b6=1;
    return 0;
}

void *thread17(void *arg)
{
    b7=1;
    return 0;
}

void *thread18(void *arg)
{
    b8=1;
    return 0;
}

void *thread19(void *arg)
{
    b9=1;
    return 0;
}

void *thread20(void *arg)
{
    b10=1;
    return 0;
}

void *thread21(void * arg)
{
    c1=1;
    return 0;
}

void *thread22(void *arg)
{
    c2=1;
    return 0;
}

void *thread23(void *arg)
{
    c3=1;
    return 0;
}

void *thread24(void *arg)
{
    c4=1;
    return 0;
}

void *thread25(void *arg)
{
    c5=1;
    return 0;
}

void *thread26(void * arg)
{
    c6=1;
    return 0;
}

void *thread27(void *arg)
{
    c7=1;
    return 0;
}

void *thread28(void *arg)
{
    c8=1;
    return 0;
}

void *thread29(void *arg)
{
    c9=1;
    return 0;
}

void *thread30(void *arg)
{
    c10=1;
    return 0;
}

int main()
{
    pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;
    pthread_t t11,t12,t13,t14,t15,t16,t17,t18,t19,t20;
    pthread_t t21,t22,t23,t24,t25,t26,t27,t28,t29,t30;

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
    pthread_create(&t21, 0, thread21, 0);
    pthread_create(&t22, 0, thread22, 0);
    pthread_create(&t23, 0, thread23, 0);
    pthread_create(&t24, 0, thread24, 0);
    pthread_create(&t25, 0, thread25, 0);
    pthread_create(&t26, 0, thread26, 0);
    pthread_create(&t27, 0, thread27, 0);
    pthread_create(&t28, 0, thread28, 0);
    pthread_create(&t29, 0, thread29, 0);
    pthread_create(&t30, 0, thread30, 0);

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
    pthread_join(t21, 0);
    pthread_join(t22, 0);
    pthread_join(t23, 0);
    pthread_join(t24, 0);
    pthread_join(t25, 0);
    pthread_join(t26, 0);
    pthread_join(t27, 0);
    pthread_join(t28, 0);
    pthread_join(t29, 0);
    pthread_join(t30, 0);

    __VERIFIER_assert( a1 || a2 || a3 || a4 || a5 || a6 || a7 || a8 || a9 || a10 );

    return 0;
}

