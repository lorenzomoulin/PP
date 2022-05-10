#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct thread_data {
   int n;
   int result;
} thread_data;

void *isPrime(void *arg);

int main(int argc, char **argv) {
    int n=atoi(argv[1]); 
    //printf("n=%d\n", n);

    int i;
    thread_data tdata[n];
    pthread_t threads[n];

    for (i=0; i<n; i++) {
        tdata[i].n=i;
        pthread_create(&(threads[i]), NULL, isPrime, &(tdata[i]));
    }

    for (i=0; i<n; i++) {
        pthread_join(threads[i], NULL);
        if (tdata[i].result==0) {
            printf("%d is not a prime number\n", i);
        } 
        else {
            printf("%d is a prime number\n", i);
        }    
    }
    printf("Fim!\n");
}

void *isPrime(void *arg) {
    thread_data *tdata = (thread_data *) arg;
    int n = tdata->n;
    int i;

    // 0 and 1 are not prime numbers
    if ((n==0)||(n==1)) {
       //printf("is_prime(%d)=0\n", *n);
       tdata->result = 0;
    }

    for (i=2; i<=n/2; ++i) {
    // if n is divisible by i, then n is not prime
    // change flag to 0 for not prime numbers
        if (n%i==0) {
           //printf("is_prime(%d)=0\n", *n);
           //pthread_exit((void *) 0);
	       tdata->result = 0;
           break;
        }
        tdata->result = 1;
    }

    //printf("is_prime(%d)=1\n", *n);
    pthread_exit(NULL);
}
