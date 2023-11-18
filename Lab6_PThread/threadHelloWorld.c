#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

void * PrintHelloWorld(void* arg) {
    printf("Hello World from a Thread\n");
    return NULL;
}

int main() {
    pthread_t thread;

    int err = pthread_create(&thread, NULL, PrintHelloWorld, NULL);
    assert(!err);
    printf("Created thread\n");

    err = pthread_join(thread, NULL);
    assert(!err);

    printf("Last thread to die\n");
}
