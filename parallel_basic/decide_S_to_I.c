#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_S_to_I(long row,
                   long col,
                   int num_Infected_Neighbours,
                   CELL **future,
                   struct drand48_data *randBuffer){
  if(num_Infected_Neighbours <= 0) return; // stays S

  double prob;
  switch(num_Infected_Neighbours){
    case 1: prob = PROB_S_TO_I_1; break;
    case 2: prob = PROB_S_TO_I_2; break;
    case 3: prob = PROB_S_TO_I_3; break;
    case 4: prob = PROB_S_TO_I_4; break;
    case 5: prob = PROB_S_TO_I_5; break;
    case 6: prob = PROB_S_TO_I_6; break;
    case 7: prob = PROB_S_TO_I_7; break;
    default: prob = PROB_S_TO_I_8; break;
  }

  double chance = 0.0;
  drand48_r(randBuffer, &chance);

  #if DEBUG_LEVEL > 1
  printf("chance = %lf\n", chance);
  printf("prob S->I = %lf\n", prob);
  #endif

  if(chance <= prob){
    future[row][col].state = 'I';
    #if DEBUG_LEVEL > 1
    printf("S -> I\n\n");
    #endif
  }
}
