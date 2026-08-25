#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_D_to_Empty(long row,
                       long col,
                       CELL **current,
                       CELL **future){
  if(current[row][col].counter_D_to_Empty == 0){
    // Make cell empty
    future[row][col].state = ' ';
    future[row][col].counter_D_infectious = 0;
    #if DEBUG_LEVEL > 1
    printf("D -> Empty\n\n");
    #endif
  } else {
    // Decrement D_to_Empty counter
    future[row][col].counter_D_to_Empty--;

    // Decrement funeral infectiousness window if still active
    if(future[row][col].counter_D_infectious > 0)
      future[row][col].counter_D_infectious--;

    #if DEBUG_LEVEL > 1
    printf("State stays as D\n\n");
    #endif
  }
}
