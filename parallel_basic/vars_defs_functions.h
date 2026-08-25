//
// Global Variables, Definitions and function prototypes for the parallel Basic Model
//

#ifndef VARS_AND_DEFS
#define VARS_AND_DEFS

#include <stdio.h>
#include <pthread.h>

#define DEBUG_LEVEL 0

#define ROWS 40
#define COLS 40
#define TOTAL_DAYS 60
#define OUTPUT_FREQ 10

//Susceptible to Infective Parameters
#define PROB_S_TO_I_1 0.90
#define PROB_S_TO_I_2 0.91
#define PROB_S_TO_I_3 0.92
#define PROB_S_TO_I_4 0.93
#define PROB_S_TO_I_5 0.94
#define PROB_S_TO_I_6 0.95
#define PROB_S_TO_I_7 0.96
#define PROB_S_TO_I_8 0.97

//Infective to Recovered or Dead Parameters
#define BASE_PROB_I_TO_D 0.1
#define BASE_TIME_I_TO_R 21
#define MIN_TIME_I_TO_R 7
#define MAX_TIME_I_TO_R 30
#define BASE_TIME_D_to_EMPTY 3

// Funeral transmission window (dead remains infectious while counter_D_infectious > 0)
#define FUNERAL_DAYS 2

//Variable to reduce computation for calculating random time ranges for I->R
extern unsigned int time_range_I_to_R_plusOne;

//Cell Type-definition
typedef struct cell {
  char state;
  int counter_I_to_R;
  int counter_D_infectious;
  int counter_D_to_Empty;
} CELL;

// Forward declaration for re-entrant drand48 state
struct drand48_data;

// Parallel globals
extern int thread_count;
extern pthread_barrier_t barrier;
extern CELL **current;
extern CELL **future;
extern FILE *fp_daySIRD;
extern unsigned long *localS;
extern unsigned long *localI;
extern unsigned long *localR;
extern unsigned long *localD;

// Function Prototypes
void initialiseWorld(CELL **current, CELL **future, unsigned long *ptr_to_numS, unsigned long *ptr_to_numI);
void outputWorld(int day, CELL **current);
void outputDaySIRD(FILE *fp_daySIRD, int day, unsigned long numS, unsigned long numI, unsigned long numR, unsigned long numD);
int countInfectedNeighbours(long row, long col, CELL **current);
void decide_S_to_I(long row, long col, int num_Infected_Neighbours, CELL **future, struct drand48_data *randBuffer);
void decide_I_to_RorD(long row, long col, CELL **current, CELL **future, struct drand48_data *randBuffer);
void decide_D_to_Empty(long row, long col, CELL **current, CELL **future);
void* child_thread(void* rank);

#endif
