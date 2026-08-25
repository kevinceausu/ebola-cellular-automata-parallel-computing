#include <stdio.h>
#include "vars_defs_functions.h"


void outputDaySIRD(FILE *fp_DaySIRD, int day,
		    unsigned long numS,
		    unsigned long numI,
		    unsigned long numR,
		    unsigned long numD){


  #if DEBUG_LEVEL > 0
  printf("Day\t S\t I\t R\t D\n");
  printf("%d\t %ld\t %ld\t %ld\t %ld\n", day, numS, numI, numR, numD);
  #endif

  fprintf(fp_DaySIRD, "%d %ld %ld %ld %ld\n", day, numS, numI, numR, numD);

}
