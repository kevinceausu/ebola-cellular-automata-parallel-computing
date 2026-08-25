# ebola-cellular-automata-parallel-computing

# Ebola Virus Spread Simulation — Parallel Computing

A parallel computing project that simulates the spread of the Ebola virus using a two-dimensional Cellular Automata model.

The project was developed in C using POSIX Pthreads and includes both a basic SIRD model and an extended SEIRD model with latent infection. The simulations are designed to run across multiple CPU threads, with the population divided into regions of the simulation grid and synchronised between generations.

## Project Overview

The simulation represents a population as a two-dimensional grid in which each cell represents an individual or an empty location.

Each individual can transition between different epidemiological states depending on the states of neighbouring cells and the probability rules defined by the model.

The simulation uses a **Moore neighbourhood**, meaning that each cell considers its eight surrounding neighbours when determining whether its state should change.

Two models were implemented:

### Basic SIRD Model

The basic model uses four states:

- **S — Susceptible**
- **I — Infective**
- **R — Recovered**
- **D — Dead**

The model simulates the spread of infection from an initial infected individual ("Patient Zero") through the surrounding population.

### Latent Infection SEIRD Model

The second model extends the basic model by introducing an exposed state:

- **S — Susceptible**
- **E — Exposed**
- **I — Infective**
- **R — Recovered**
- **D — Dead**

The exposed state represents individuals who have been infected but have not yet become infectious.

## Parallel Computing

The core of the project is the parallel implementation using **POSIX Pthreads**.

The two-dimensional simulation grid is divided between multiple worker threads, with each thread responsible for processing a section of rows.

Each generation follows the same general process:

1. Each thread processes its assigned rows.
2. The states of neighbouring cells are examined.
3. State transitions are calculated according to the model's rules.
4. Changes are written to a separate future-world grid.
5. Threads synchronise at the end of the generation.
6. The future world becomes the current world.
7. Simulation statistics and world data are written to output files.
8. The threads proceed to the next generation.

A barrier is used to synchronise the threads between generations so that all threads complete the current generation before processing the next one.

## Cellular Automata

The simulation uses a two-dimensional Cellular Automata approach.

Each cell examines its **Moore neighbourhood** consisting of the eight surrounding cells.

Periodic boundary conditions are used, meaning that the edges of the simulation wrap around to the opposite side of the grid. This allows every cell to have the same number of neighbouring positions.

The simulation maintains separate current and future worlds so that changes made during a generation do not immediately affect the processing of neighbouring cells.

## Project Structure

```text
ebola-cellular-automata-parallel-computing/
│
├── parallel_basic/
│   ├── child_thread.c
│   ├── countInfectedNeighbours.c
│   ├── decide_D_to_Empty.c
│   ├── decide_I_to_RorD.c
│   ├── decide_S_to_I.c
│   ├── initialiseWorld.c
│   ├── outputDaySIRD.c
│   ├── outputWorld.c
│   ├── parallel_basic.c
│   ├── timer.h
│   ├── vars_defs_functions.h
│   ├── Makefile
│   ├── daySIRD.gnu
│   ├── daySIRD.png
│   └── data/
│
├── parallel_latent/
│   ├── child_thread.c
│   ├── countInfectedNeighbours.c
│   ├── decide_D_to_Empty.c
│   ├── decide_E_to_I.c
│   ├── decide_I_to_RorD.c
│   ├── decide_S_to_E.c
│   ├── initialiseWorld.c
│   ├── outputDaySEIRD.c
│   ├── outputWorld.c
│   ├── parallel_latent.c
│   ├── timer.h
│   ├── vars_defs_functions.h
│   ├── Makefile
│   ├── daySEIRD.gnu
│   ├── daySEIRD.png
│   └── data/
│
└── docs/
    ├── Parallel Presentation.pdf
    └── Project Plan.pdf


# Technologies
C
POSIX Pthreads
GNU Make
Bash
Gnuplot
Linux/UNIX development environment

# Simulation Output

The programs generate simulation data for each generation, including:

Number of susceptible individuals
Number of exposed individuals
Number of infective individuals
Number of recovered individuals
Number of deaths
Total population

The generated world data can be used with visualisation tools to observe how the infection spreads through the simulated population over time.

Population statistics are also written to data files and can be plotted using Gnuplot.

# Visualisation

The project includes Gnuplot scripts for plotting population data over time.

# Basic SIRD Model

# SEIRD Model with Latent Infection

# Building the Programs

Both implementations include their own Makefile.

To build the basic SIRD implementation:

cd parallel_basic
make

To build the latent-infection SEIRD implementation:

cd parallel_latent
make

The programs can then be executed according to the configuration defined in their respective source files and Makefiles.

# Results and Performance

An important part of the project was evaluating the performance difference between serial and parallel implementations and investigating the effect of different numbers of threads.

The parallel implementation was designed to reduce simulation time by distributing the computational workload across multiple CPU cores.

Performance depends on factors including:

Number of threads
Number of available CPU cores
Simulation grid size
Number of generations
Synchronisation overhead
Workload per thread

The project therefore demonstrates the practical limitations of parallel speed-up rather than assuming that doubling the number of threads will automatically halve execution time.

# Documentation

The docs directory contains the project documentation and presentation:

Parallel Presentation — project methodology, Cellular Automata model, implementation, testing, results and conclusions.
Project Plan — initial project planning and development schedule.

#University Project

This project was developed as part of the Parallel Computing (COMP H3036) module.

The project focused on applying parallel programming techniques to a computationally intensive simulation problem using C and POSIX Pthreads.
