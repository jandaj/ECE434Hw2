/*
In order to make it so that the parent thread prints the fibonacci sequence while the child thread is populating the array, I malloced the array in the parent thread, passed it to the child thread and then the parent prints the number when ever the child thread populates a new number in the sequence.  In order to better demonstrate this there is a delay (sleep) of 1 second inserted for every number populated into the sequence.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <pthread.h> 

void* fib(void* input) 
{ 
    int* seq = (int*)input;
    printf("Generating numbers...\n");
    int i = 0;
    while(1) {
        sleep(1);
        int last = 0;
        if(seq[i] == -2) {
            last = 1;
        }
        if(i == 0) {
            seq[i] = 0;
        }
        else if(i == 1) {
            seq[i] = 1;
        }
        else{
            seq[i] = seq[i-1] + seq[i-2];
        }
        if(last) {
            break;
        }
        i++;
    }
    printf("Done generating numbers.\n");
    return NULL;
} 
   
int main() 
{ 
    printf("Number of Fibonacci numbers to generate?\n");
    int numberOfFib = 0;
    scanf("%d",&numberOfFib);
    if(numberOfFib > 47) {
        printf("I'm not going to do that.  The fibonacci number is going to overflow.\n");
        exit(-1);
    }
    if(numberOfFib == 0) {
        exit(0);
    }
    int* seq = (int*)malloc(sizeof(int) * numberOfFib);
    memset(seq,-1,sizeof(int)*numberOfFib);
    seq[numberOfFib-1] = -2;
    pthread_t thread_id; 
    pthread_create(&thread_id, NULL,fib, (void *)seq); 
    int i;    
    for(i = 0; i < numberOfFib; i++) {
        while(1) {
            if(seq[i] > -1) {
                printf("%d\n",seq[i]);
                break;
            }
        }
    }
    pthread_join(thread_id, NULL);
    printf("Done.\n"); 
    exit(0); 
}
