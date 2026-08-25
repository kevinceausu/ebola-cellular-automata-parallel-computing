//
// Global Variables, Definitions and function prototypes for the parallel Latent (SEIR) Model
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

// Susceptible to Exposed Parameters (S -> E)
#define PROB_S_TO_E_1 0.90
#define PROB_S_TO_E_2 0.91
#define PROB_S_TO_E_3 0.92
#define PROB_S_TO_E_4 0.93
#define PROB_S_TO_E_5 0.94
#define PROB_S_TO_E_6 0.95
#define PROB_S_TO_E_7 0.96
#define PROB_S_TO_E_8 0.97

// Infective to Recovered or Dead Parameters
#define BASE_PROB_I_TO_D 0.1
#define BASE_TIME_I_TO_R 21
#define MIN_TIME_I_TO_R 7
#define MAX_TIME_I_TO_R 30
#define BASE_TIME_D_to_EMPTY 3

// Funeral transmission window
#define FUNERAL_DAYS 2

// Exposed to Infective Parameters (E -> I)
#define MIN_TIME_E_TO_I 1
#define MAX_TIME_E_TO_I 7

extern unsigned int time_range_I_to_R_plusOne;
extern unsigned int time_range_E_to_I_plusOne;

typedef struct cell {
  char state;
  int counter_E_to_I;
  int counter_I_to_R;
  int counter_D_infectious;
  int counter_D_to_Empty;
} CELL;

struct drand48_data;

// Parallel globals
extern int thread_count;
extern pthread_barrier_t barrier;
extern CELL **current;
extern CELL **future;
extern FILE *fp_daySEIRD;
extern unsigned long *localS;
extern unsigned long *localE;
extern unsigned long *localI;
extern unsigned long *localR;
extern unsigned long *localD;

// Prototypes
void initialiseWorld(CELL **current, CELL **future, unsigned long *ptr_to_numS, unsigned long *ptr_to_numE, unsigned long *ptr_to_numI);
void outputWorld(int day, CELL **current);
void outputDaySEIRD(FILE *fp_daySEIRD, int day, unsigned long numS, unsigned long numE, unsigned long numI, unsigned long numR, unsigned long numD);
int countInfectedNeighbours(long row, long col, CELL **current);
void decide_S_to_E(long row, long col, int num_Infected_Neighbours, CELL **future, struct drand48_data *randBuffer);
void decide_E_to_I(long row, long col, CELL **current, CELL **future);
void decide_I_to_RorD(long row, long col, CELL **current, CELL **future, struct drand48_data *randBuffer);
void decide_D_to_Empty(long row, long col, CELL **current, CELL **future);
void* child_thread(void* rank);

#endif
