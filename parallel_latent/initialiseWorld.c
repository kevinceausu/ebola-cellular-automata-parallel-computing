#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void initialiseWorld(CELL **current,
		     CELL **future,
		     unsigned long *ptr_to_numS,
		     unsigned long *ptr_to_numE,
		     unsigned long *ptr_to_numI){

  long i, j, randRow, randCol;

  for(i=0; i<ROWS; i++)
    for(j=0; j<COLS; j++){

      current[i][j].state = 'S';
      current[i][j].counter_E_to_I = lrand48()%time_range_E_to_I_plusOne + MIN_TIME_E_TO_I;
      current[i][j].counter_I_to_R = lrand48()%time_range_I_to_R_plusOne + MIN_TIME_I_TO_R;
      current[i][j].counter_D_infectious = 0;
      current[i][j].counter_D_to_Empty = BASE_TIME_D_to_EMPTY;
      
      future[i][j] = current[i][j];
      
      (*ptr_to_numS)++;
    }

  randRow = lrand48()%ROWS;
  randCol = lrand48()%COLS;

  current[randRow][randCol].state = 'I';
  current[randRow][randCol].counter_D_infectious = 0;
  future[randRow][randCol] = current[randRow][randCol];
  (*ptr_to_numS)--;
  (*ptr_to_numI)++;

  // Exposed count starts at 0 (all start as Susceptible except patient zero)
  *ptr_to_numE = 0;

  #if DEBUG_LEVEL > 0
  printf("InitialiseWorld: numS = %ld, numI = %ld\n\n", *ptr_to_numS, *ptr_to_numI);
  #endif
}
