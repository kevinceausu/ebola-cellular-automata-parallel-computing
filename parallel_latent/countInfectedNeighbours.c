#include <stdio.h>
#include "vars_defs_functions.h"


int countInfectedNeighbours(long row,
			    long col,
			    CELL **current){

  int i, j;
  int local_num_Infected_Neighbours = 0;

  #if DEBUG_LEVEL > 1
  printf("Cell[%d][%d] is Susceptible:\n", row, col);
  #endif
  
  //Check neighbours of the candidate cell
  for(i=row-1; i<=row+1; i++)
    for(j=col-1; j<=col+1; j++){
      
      //Don't include the candidate cell
      //In avoiding the candidate cell, it is more efficient
      // to check that we are NOT looking at it and then
      // proceed to the next step rather than check than that
      // we ARE looking at it, which would then require us to
      // put in an "else" statement to avoid it	
      if(i != row || j != col){

        #if DEBUG_LEVEL > 1
	printf("  Neighbour[%d][%d]\n",(i+ROWS)%ROWS, (j+COLS)%COLS);
	#endif
	
	CELL neigh = current[(i+ROWS)%ROWS][(j+COLS)%COLS];
	// Infectious neighbours are living infective (I) and recently-dead (D)
	// while their funeral window counter is > 0.
	if(neigh.state == 'I' || (neigh.state == 'D' && neigh.counter_D_infectious > 0))
	  local_num_Infected_Neighbours++;
	
      }
    }

  return local_num_Infected_Neighbours;

}
  
