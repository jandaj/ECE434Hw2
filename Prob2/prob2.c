/*
The following multithreaded program generates the fibonacci sequence, where the parent thread inquiries the user about how many fibonacci sequence numbers they wish to generate and the spawned child thread mallocs an array of numbers, populates the array with the desired sequence and then returns the array to the parent array for printing.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

void* fib(void* input) 
{ 
    int number = *(int *) input;
    if(number == 0) {
        return NULL;
    }
    int* seq = (int*)malloc(sizeof(int) * number);
    printf("Generating %d numbers...\n",number);
    int i;
    for(i = 0; i < number; i++) {
        if(i == 0) {
            seq[i] = 0;
        }
        else if(i == 1) {
            seq[i] = 1;
        }
        else{
            seq[i] = seq[i-1] + seq[i-2];
        }
    }
    printf("Done generating numbers.\n");
    return (void*) seq; 
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
    pthread_t thread_id; 
    pthread_create(&thread_id, NULL,fib, &numberOfFib); 
    void ** seq;
    pthread_join(thread_id, seq);
    for(int i = 0; i < numberOfFib; i++) {
        printf("%d\n",((int*)*seq)[i]);
    }
    printf("Done.\n"); 
    exit(0); 
}
