#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define size 100
#define thread_max 10
int a[size];
int MAX,MIN;
void *find(void *args) {
  
   MAX = a[0];;
   MIN = a[0];
  
  for(int i=1;i<size;i++)
    {
      if(a[i]>MAX)
      {
        MAX=a[i];
      }
    }
  for(int i=1;i<size;i++)
    {
      if(a[i]<MIN)
      {
        MIN=a[i];
      }
    }
}
int main() {
  pthread_t t[thread_max];
  for (int i = 0; i < size; i++) {
    a[i] = rand() % 100;
  }
  
  for(int i=0;i<size;i++)
    {
      printf("%d ",a[i]);
    }
  for (int i = 0; i < thread_max; i++) {
    pthread_create(&t[i], NULL, find, NULL);
  }

  for (int i = 0; i < thread_max; i++) {
    pthread_join(t[i], NULL);
  }
  printf("Maximum Number of the array is %d\n", MAX);
  printf("Minimum Number of the array is %d\n", MIN);
}