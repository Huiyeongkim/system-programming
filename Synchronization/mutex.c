#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define THREADS 4
#define N 3000

int primes[N];
int pflag[N];
int total = 0;
pthread_mutex_t mutex;

int is_prime(int v) 
{
    int i;
    int bound = floor(sqrt ((double)v)) + 1;
    for (i = 2; i < bound; i++) {
        /* No need to check against known composites */ 
        if (!pflag[i])
            continue;

        if (v % i == 0) {
            pflag[v] = 0;
            return 0;
        }
    }
    return (v > 1); 
}

void *work(void *arg)
{
    int start;
    int end;
    int i;
    start = (N/THREADS) * (*(int *)arg) ;
    end = start + N/THREADS;

    for (i = start; i < end; i++) {
	if ( is_prime(i) ) {
            pthread_mutex_lock(&mutex); 
            primes[total] = i;
            total++;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int main(int argn, char **argv)
{
    int i;
    pthread_t tids[THREADS-1];
    int index[THREADS-1];
    pthread_mutex_init(&mutex, NULL); 
    for (i = 0; i < N; i++) {
        pflag[i] = 1; 
    }
    
    for (i = 0; i < THREADS-1; i++) {
        index[i] = i;
        pthread_create(&tids[i], NULL, work, (void *)&index[i]);
    }
    index[THREADS-1] = THREADS-1;
    work((void *)&index[THREADS-1]);
    
    for (i = 0; i < THREADS-1; i++) {
        pthread_join(tids[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of prime numbers between 2 and %d: %d\n",
           N, total);
    for (i = 0; i < total; i++) {
        printf("%d\n", primes[i]);
    }


    return 0;
}
