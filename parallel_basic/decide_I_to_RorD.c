#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_I_to_RorD(long row,
                      long col,
                      CELL **current,
                      CELL **future,
                      struct drand48_data *randBuffer){
  double chance = 0.0;
  drand48_r(randBuffer, &chance);

  // If chance <= BASE_PROB_I_TO_D, the infective dies
  if(chance <= BASE_PROB_I_TO_D){
    future[row][col].state = 'D';
    future[row][col].counter_D_infectious = FUNERAL_DAYS;
    future[row][col].counter_D_to_Empty = BASE_TIME_D_to_EMPTY;
    #if DEBUG_LEVEL > 1
    printf("I -> D\n\n");
    #endif
    return;
  }

  // Otherwise, check if time to recover
  if(current[row][col].counter_I_to_R == 0){
    future[row][col].state = 'R';
    future[row][col].counter_D_infectious = 0;
    #if DEBUG_LEVEL > 1
    printf("I -> R\n\n");
    #endif
  } else {
    // Not yet recovered; decrement countdown
    future[row][col].counter_I_to_R--;
  }
}
