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
        while (buf.currentLoad >= buf.capacity){}
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
        while (buf.currentLoad == 0){}
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
    // 2 CONSUMERS AND 2 PRODUCERS TO GET RACE CONDITION FASTER
    pthread_t consumer1, consumer2;
    pthread_t producer1, producer2;
    pthread_create(&producer1, NULL, &produce, NULL);
    pthread_create(&consumer1, NULL, &consume, NULL);
    pthread_create(&producer2, NULL, &produce, NULL);
    pthread_create(&consumer2, NULL, &consume, NULL);
    pthread_join(producer1, NULL);
    pthread_join(producer2, NULL);
    pthread_join(consumer1, NULL);
    pthread_join(consumer2, NULL);
    return 0;
}