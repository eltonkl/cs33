#include "csapp.h"

void *thread(void *vargp);

int main(int argc, char *argv[])
{
    int num_threads = 1;
    if(argc > 1)
    {
        num_threads = atoi(argv[1]);    
        if(num_threads < 0)
            exit(1);
    }
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    for(int i = 0; i < num_threads; i++)
    {
        Pthread_create(&threads[i], NULL, thread, NULL);
    }
    for(int i = 0; i < num_threads; i++)
        Pthread_join(threads[i], NULL);
    free(threads);
    exit(0);
}

void *thread(void *vargp)
{
    printf("Hello, world!\n");
    return NULL;
}
