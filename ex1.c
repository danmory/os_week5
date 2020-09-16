#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 5

pthread_mutex_t mutex;
int currentThreadNumber = 0;

void* show(void* p){
    while(1) {
        pthread_mutex_lock(&mutex);
            int id = currentThreadNumber;
            printf("Thread #%i is working\n", id);
            printf("Actions... \n");
            printf("Thread #%i is done \n", id);
            currentThreadNumber++;
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }

}

int main(){

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[N];

    for (int i = 0; i < N; i++) {
        pthread_create(&(threads[i]), NULL, show, NULL);
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}