#include <stdio.h>
#include <stdlib.h>

#include "vars_defs_functions.h"

void decide_E_to_I(long row,
                   long col,
                   CELL **current,
                   CELL **future){
  if(current[row][col].counter_E_to_I == 0){
    future[row][col].state = 'I';
  } else {
    future[row][col].counter_E_to_I--;
  }
}
