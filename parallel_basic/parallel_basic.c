#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "timer.h"
#include "vars_defs_functions.h"


unsigned int time_range_I_to_R_plusOne;

//parallel globals
int thread_count = 1;
pthread_barrier_t barrier;
CELL **current = NULL;
CELL **future = NULL;
FILE *fp_daySIRD = NULL;

unsigned long *localS = NULL;
unsigned long *localI = NULL;
unsigned long *localR = NULL;
unsigned long *localD = NULL;

//child thread entry
void* child_thread(void* rank);

static void allocate_worlds(void){
long i;
current = (CELL**)malloc(ROWS * sizeof(CELL*));
future = (CELL**)malloc(ROWS * sizeof(CELL));
if(!current || !future){
    perror("malloc");
    exit(EXIT_FAILURE);
}
for(i=0;i<ROWS;i++){
    current[i] = (CELL*)malloc(COLS * sizeof(CELL));
    future[i] = (CELL*)malloc(COLS * sizeof(CELL));
    if(!current[i] || !future[i]){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}
}

static void free_worlds(void){
    long i;
    if(current){
    for(i=0;i<ROWS;i++) free(current[i]);
    free(current);
    current = NULL;
    }
    if(future){
    for(i=0;i<ROWS;i++) free(future[i]);
    free(future);
    future = NULL;
    }
}

int main(int argc, char* argv[]){
    double start, finish, elapsed;
if(argc < 2){
    fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
    return EXIT_FAILURE;
}

thread_count = atoi(argv[1]);
if(thread_count <= 0){
    fprintf(stderr, "thread_count must be > 0\n");
    return EXIT_FAILURE;
}
if(ROWS % thread_count != 0){
    fprintf(stderr, "Error: ROWS (%d) must be divisible by thread_count (%d)\n", ROWS, thread_count);
    return EXIT_FAILURE;
}

//countdown for I to R
time_range_I_to_R_plusOne = MAX_TIME_I_TO_R - MIN_TIME_I_TO_R + 1;
allocate_worlds();

unsigned long numS = 0, numI = 0, numR = 0, numD = 0;

//output file
fp_daySIRD = fopen("data/daySIRD.dat", "w");
if(!fp_daySIRD){
    perror("fopen(data/daySIRD.dat)");
    return EXIT_FAILURE;
}

//random seed
srand48((long)time(NULL));
initialiseWorld(current, future, &numS, &numI);

//day 0 output
outputWorld(0, current);
outputDaySIRD(fp_daySIRD, 0, numS, numI, numR, numD);

//allocate arrays per-thread count
localS = (unsigned long*)calloc(thread_count, sizeof(unsigned long));
localI = (unsigned long*)calloc(thread_count, sizeof(unsigned long));
localR = (unsigned long*)calloc(thread_count, sizeof(unsigned long));
localD = (unsigned long*)calloc(thread_count, sizeof(unsigned long));
if(!localS || !localI || !localR || !localD){
    perror("calloc");
    return EXIT_FAILURE;
}

if(pthread_barrier_init(&barrier, NULL, (unsigned)thread_count) != 0){
    fprintf(stderr, "Failed to init barrier\n");
    return EXIT_FAILURE;
}

pthread_t* thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
if(!thread_handles){
    perror("malloc(thread_handles)");
    return EXIT_FAILURE;
}

GET_TIME(start);

for(long thread=0; thread<thread_count; thread++){
if(pthread_create(&thread_handles[thread], NULL, child_thread, (void*)thread) != 0){
    fprintf(stderr, "Error creating thread %ld\n", thread);
    return EXIT_FAILURE;
}
}

for(long thread=0; thread<thread_count; thread++){
    pthread_join(thread_handles[thread], NULL);
}

GET_TIME(finish);
elapsed = finish - start;
printf("Elapsed time = %lf\n", elapsed);

pthread_barrier_destroy(&barrier);

free(thread_handles);
fclose(fp_daySIRD);

free(localS);
free(localI);
free(localR);
free(localD);
localS = localI = localR = localD = NULL;

free_worlds();
return 0;
}
