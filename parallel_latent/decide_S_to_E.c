#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_S_to_E(long row,
                   long col,
                   int num_Infected_Neighbours,
                   CELL **future,
                   struct drand48_data *randBuffer){
  if(num_Infected_Neighbours <= 0) return;

  double prob=0.0;
  switch(num_Infected_Neighbours){
    case 1: prob = PROB_S_TO_E_1; break;
    case 2: prob = PROB_S_TO_E_2; break;
    case 3: prob = PROB_S_TO_E_3; break;
    case 4: prob = PROB_S_TO_E_4; break;
    case 5: prob = PROB_S_TO_E_5; break;
    case 6: prob = PROB_S_TO_E_6; break;
    case 7: prob = PROB_S_TO_E_7; break;
    default: prob = PROB_S_TO_E_8; break;
  }

  double chance=0.0;
  drand48_r(randBuffer, &chance);

  if(chance <= prob){
    future[row][col].state = 'E';
  }
}
