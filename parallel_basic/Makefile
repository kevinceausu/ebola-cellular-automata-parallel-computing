# Makefile for Parallel Basic Model (Pthreads)

CC = gcc
CFLAGS = -g -Wall

DEPS = vars_defs_functions.h timer.h

OBJ = parallel_basic.o \
      child_thread.o \
      initialiseWorld.o \
      outputDaySIRD.o \
      outputWorld.o \
      countInfectedNeighbours.o \
      decide_S_to_I.o \
      decide_I_to_RorD.o \
      decide_D_to_Empty.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

parallel_basic: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f *.o parallel_basic
