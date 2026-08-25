#include <stdio.h>
#include "vars_defs_functions.h"

void outputDaySEIRD(FILE *fp_daySEIRD, int day,
                    unsigned long numS,
                    unsigned long numE,
                    unsigned long numI,
                    unsigned long numR,
                    unsigned long numD)
{
  // Format: day S E I R D
  fprintf(fp_daySEIRD, "%d %lu %lu %lu %lu %lu\n", day, numS, numE, numI, numR, numD);
}
