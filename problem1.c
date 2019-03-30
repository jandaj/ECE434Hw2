#include <stdio.h> /* For printf, scanf, puts */
#include <pthread.h> /* For various thread functions */
#include <math.h> /* For sqrt */
#include <stdlib.h> /* For calloc */
#include <string.h>
void *outputprime(void *var1){
    int *ci;
    ci =(int *) var1;
    printf("%d is a prime\n", *ci);
    return NULL;
}

int main (int argc, char *argv[]){
    /*
     The program creates a thread that outputs all the prime numbers less than or equal to the number entered by the user.
     */
    
    long v1 = strtol(argv[1],NULL,0);
    int last = v1;
    int prime[last+1];
    for (int i = 0; i<last; i++){
        prime[i] = 1;
    }

    for (int i = 2; i*i<=last;i++){
        if(prime[i]==1){
            for(int j = i*i;j<=last;j+=i){
                prime[j] =0;
            }
        }
    }
    for (int i =2;i<last;i++){
        if (prime[i]){
            pthread_t tid;
            pthread_create(&tid, NULL, outputprime, & i);
            pthread_join(tid, NULL);
        }
    }
}
