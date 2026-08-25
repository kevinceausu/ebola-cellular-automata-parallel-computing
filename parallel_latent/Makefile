# Makefile for Parallel Latent (SEIR) Model (Pthreads)

CC = gcc
CFLAGS = -g -Wall

DEPS = vars_defs_functions.h timer.h

OBJ = parallel_latent.o \
      child_thread.o \
      initialiseWorld.o \
      outputDaySEIRD.o \
      outputWorld.o \
      countInfectedNeighbours.o \
      decide_S_to_E.o \
      decide_E_to_I.o \
      decide_I_to_RorD.o \
      decide_D_to_Empty.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

parallel_latent: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

clean:
	rm -f *.o parallel_latent
