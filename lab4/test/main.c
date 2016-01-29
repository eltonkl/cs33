#include <mcheck.h>
#include <pthread.h>

void* func()
{
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    setenv("MALLOC_TRACE", "mtrace.out", 0);
    mtrace();
    pthread_t thread;
    pthread_create(&thread, NULL, func, NULL);
    pthread_join(thread, NULL);
    muntrace();
}
