#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_D_to_Empty(long row,
                       long col,
                       CELL **current,
                       CELL **future){
  if(current[row][col].counter_D_to_Empty == 0){
    future[row][col].state = ' ';
    future[row][col].counter_D_infectious = 0;
  } else {
    future[row][col].counter_D_to_Empty--;
    if(future[row][col].counter_D_infectious > 0)
      future[row][col].counter_D_infectious--;
  }
}
