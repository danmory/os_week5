#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 10

struct Buffer{
    int capacity;
    int currentLoad;
} buf;

void* produce(void* arg){
    while (1){
        while (buf.currentLoad >= buf.capacity){
            /* sleeping */
        }
        if (buf.currentLoad >= buf.capacity){
            printf("error, trying to produce into the full buffer(RACE CONDITION) \n");
            exit(1);
        }else{
            printf("producing.. \n");
            buf.currentLoad++;
            if (buf.currentLoad > buf.capacity){
                printf("error, buffer load is more than capacity(RACE CONDITION) \n");
                exit(1);
            }
        }
    }
}

void* consume(void* arg){
    while(1){
        while (buf.currentLoad == 0){
            /* sleeping */
        }
        if (buf.currentLoad == 0){
            printf("error, trying to consume from the empty buffer(RACE CONDITION) \n");
            exit(1);
        }else{
            printf("consuming.. \n");
            buf.currentLoad--;
            if (buf.currentLoad < 0){
                printf("error, load of a buffer is negative(RACE CONDITION) \n");
                exit(1);
            }
        }
    }
}

int main(){
    buf.capacity = N;
    buf.currentLoad = 0;
    pthread_t consumer;
    pthread_t producer;
    pthread_create(&producer, NULL, &produce, NULL);
    pthread_create(&consumer, NULL, &consume, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    return 0;
}