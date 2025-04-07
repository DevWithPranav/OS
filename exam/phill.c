#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick [5];

void *philos(void*);
void eat(int);

void main(){
     int i,n[5];
     pthread_t T [5];
     
     for(int i=0; i<5; i++){
         sem_init(&chopstick[i],0,1);
     }
     
     for(int i=0; i<5; i++){
         n[i] = i;
         pthread_create(&T[i], NULL, philos,(void*)&n[i]);
     }
     
     for(int i=0; i<5; i++){
         pthread_join(T[i],NULL);
     }
}

void *philos(void *n){
      int ph = *(int*)n;
      
      printf("philospher %d wants to eat\n", ph);
      printf("philospher %d tries to pick left chopstick\n", ph);
      
      sem_wait(&chopstick[ph]);
      
      printf("philospher %d picks the left chopstick\n", ph);
      printf("philospher %d tries to pick right chopstick\n", ph);
      
      sem_wait(&chopstick[(ph+1)%5]);
      
      printf("philospher %d picks the right chopstick\n", ph);
      eat(ph);
      
      sleep(2);
      
      printf("philospher %d has finished eating\n", ph);
      
      sem_post(&chopstick[(ph+1)%5]);      
      printf("philospher %d leaves the right chopstick\n", ph);
      
      sem_post(&chopstick[ph]);      
      printf("philospher %d leaves the left chopstick\n", ph);
}

void eat(int ph){
     printf("philospher %d begins to eat\n", ph);
}

/*
OUTPUT

philospher 0 wants to eat
philospher 0 tries to pick left chopstick
philospher 0 picks the left chopstick
philospher 0 tries to pick right chopstick
philospher 0 picks the right chopstick
philospher 0 begins to eat
philospher 1 wants to eat
philospher 1 tries to pick left chopstick
philospher 3 wants to eat
philospher 3 tries to pick left chopstick
philospher 3 picks the left chopstick
philospher 3 tries to pick right chopstick
philospher 3 picks the right chopstick
philospher 3 begins to eat
philospher 2 wants to eat
philospher 2 tries to pick left chopstick
philospher 2 picks the left chopstick
philospher 2 tries to pick right chopstick
philospher 4 wants to eat
philospher 4 tries to pick left chopstick
philospher 0 has finished eating
philospher 0 leaves the right chopstick
philospher 0 leaves the left chopstick
philospher 3 has finished eating
philospher 3 leaves the right chopstick
philospher 3 leaves the left chopstick
philospher 1 picks the left chopstick
philospher 1 tries to pick right chopstick
philospher 4 picks the left chopstick
philospher 4 tries to pick right chopstick
philospher 4 picks the right chopstick
philospher 4 begins to eat
philospher 2 picks the right chopstick
philospher 2 begins to eat
philospher 4 has finished eating
philospher 4 leaves the right chopstick
philospher 4 leaves the left chopstick
philospher 2 has finished eating
philospher 2 leaves the right chopstick
philospher 2 leaves the left chopstick
philospher 1 picks the right chopstick
philospher 1 begins to eat
philospher 1 has finished eating
philospher 1 leaves the right chopstick
philospher 1 leaves the left chopstick

*/