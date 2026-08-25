#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "vars_defs_functions.h"

//thread updates a number of rows for each day
void* child_thread(void* rank){
long my_rank = (long)rank;
long rows_per_thread = ROWS / thread_count;
long start_row = my_rank * rows_per_thread;
long end_row = start_row + rows_per_thread;

//random state thread
struct drand48_data randBuffer;
long seed = (long)time(NULL) + (my_rank * 10007);
srand48_r(seed, &randBuffer);

for(int day = 1; day <= TOTAL_DAYS; day++){
unsigned long s=0,i=0,r=0,d=0;

for(long row = start_row; row < end_row; row++){
    for(long col = 0; col < COLS; col++){
        future[row][col] = current[row][col];
        switch(current[row][col].state){
            case 'S': {
                int n = countInfectedNeighbours(row, col, current);
                decide_S_to_I(row, col, n, future, &randBuffer);
                break;
            }
            case 'I':
            decide_I_to_RorD(row, col, current, future, &randBuffer);
            break;
            case 'D':
            decide_D_to_Empty(row, col, current, future);
            break;
            default:
            break;
        }

//count finale state for this cell
switch(future[row][col].state){
    case 'S': s++; break;
    case 'I': i++; break;
    case 'R': r++; break;
    case 'D': d++; break;
    default: break;
}
    }
}

localS[my_rank] = s;
localI[my_rank] = i;
localR[my_rank] = r;
localD[my_rank] = d;

pthread_barrier_wait(&barrier);

if(my_rank == 0){
unsigned long numS=0,numI=0,numR=0,numD=0;
for(int t=0;t<thread_count;t++){
    numS += localS[t];
    numI += localI[t];
    numR += localR[t];
    numD += localD[t];
}

//swap current and future pointers
CELL **tmp = current;
current = future;
future = tmp;

//output data
outputDaySIRD(fp_daySIRD, day, numS, numI, numR, numD);
if(day % OUTPUT_FREQ == 0){
    outputWorld(day, current);
}

#if DEBUG_LEVEL > 0
printf("Finished day %d of %d\n", day, TOTAL_DAYS);
#endif
}

//ensure output done before next day
pthread_barrier_wait(&barrier);
}
return NULL;
}

