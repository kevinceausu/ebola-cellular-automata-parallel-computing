#include <stdio.h>
#include "vars_defs_functions.h"


void outputWorld(int day, CELL **current){

  long i, j;

  char myfilename[20];
  int a = day;
  int t, m;

  sprintf(myfilename, "data/worldDDDDD.dat");
  for(t=14; t>=10; t--){
    m = a%10;
    
    myfilename[t] = (char)(48+m);
    a = a/10;
  }
  
  FILE *fp_world = fopen(myfilename, "w");

  for(i=0; i<ROWS; i++){ 
    for(j=0; j<COLS; j++){

      #if DEBUG_LEVEL > 0
      printf("%c ", current[i][j].state);
      #endif
      
      fprintf(fp_world, "%c ", current[i][j].state);
    }

    #if DEBUG_LEVEL > 0
    printf("\n");
    #endif
    
    fprintf(fp_world,"\n");
  }

  #if DEBUG_LEVEL > 0
  printf("\n");
  #endif

  fclose(fp_world);

}
