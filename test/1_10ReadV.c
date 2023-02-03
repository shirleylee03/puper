extern void abort(void); 
void reach_error(){}

#include <pthread.h>
#include <assert.h>

int data = 0;
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0;

void *thread1(void *arg)
{
  data++;
  return 0;
}

void *thread2(void *arg)
{
  a1++;
  return 0;
}

void *thread3(void *arg)
{
  a2++;
  return 0;
}

void *thread4(void *arg)
{
  if (data >= 1){
    ERROR: {reach_error();abort();}
    ;
  }
  return 0;
}

void *thread5(void *arg)
{
  a3++;
  return 0;
}

void *thread6(void *arg)
{
  a4++;
  return 0;
}

void *thread7(void *arg)
{
  a5++;
  return 0;
}

void *thread8(void *arg)
{
  a6++;
  return 0;
}

void *thread9(void *arg)
{
  a7++;
  return 0;
}

void *thread10(void *arg)
{
  a8++;
  return 0;
}

int main()
{

  pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

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

  return 0;
}
