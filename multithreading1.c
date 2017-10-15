#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS          2
#define INVALID_RETURN_VALUE (-1)

int array[] = {1,3,2,4,5,7,6,9,10,11,12,13,0,3,7,8,1,3,5,7,9,2,4,6,8,0,1,2,3,4,5,6,7,8};
int length = sizeof(array)/sizeof(array[0]);
int shared_index = 0;
pthread_mutex_t shared_index_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  shared_index_cv   = PTHREAD_COND_INITIALIZER;

void
thread_1(void *ptr)
{
    while (1) {
        sleep(1);
        pthread_mutex_lock(&shared_index_lock);        
        pthread_cond_signal(&shared_index_cv);
        pthread_cond_wait(&shared_index_cv, &shared_index_lock);         
        while (shared_index < length && array[shared_index] % 2 == 1) {               
            printf("Thread_name = odd_thread shared_index = %d\n", array[shared_index]);
            shared_index++;
        }
        pthread_cond_signal(&shared_index_cv);
        pthread_mutex_unlock(&shared_index_lock);
    }
}

void
thread_2(void *ptr)
{
    while (1) {
        sleep(1);
        pthread_mutex_lock(&shared_index_lock);        
        pthread_cond_signal(&shared_index_cv);
        pthread_cond_wait(&shared_index_cv, &shared_index_lock);            
        while (shared_index < length && array[shared_index] % 2 == 0) {                        
            printf("Thread_name = even_thread shared_index = %d\n", array[shared_index]);
            shared_index++;
        }
        pthread_cond_signal(&shared_index_cv);
        pthread_mutex_unlock(&shared_index_lock);
    }
}

int 
main(int argc, char **argv)
{
    int i;
    int rc = INVALID_RETURN_VALUE;
    pthread_t thread[MAX_THREADS];    

    printf("size: %d\n", length);

    pthread_create(&thread[0], NULL, (void *) &thread_1, NULL);
    pthread_create(&thread[1], NULL, (void *) &thread_2, NULL);


    for(i = 0; i < MAX_THREADS; i++) {
        pthread_join(thread[i], NULL);
    }

    /*
     * Cleanup
     */
    rc = pthread_mutex_destroy(&shared_index_lock);

    if (rc) {
        printf("Unable to destroy lock = main_thread\n");
    }

    rc = pthread_cond_destroy(&shared_index_cv);

    if (rc) {
        printf("Unable to destroy cv = main_thread\n");
    }

    return 0;
}
