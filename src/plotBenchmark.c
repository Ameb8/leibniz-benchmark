#include <stdio.h>

#include "../include/subprocess.h"
#include "../include/plotBenchmark.h"


#define PLOT_PRGRM_PATH "benchmark_results/plot_benchmark.py" // Path to plot creation file
#define PLOT_PRGRM_NAME "python3" // Name of executable for making plots

// Error and Success messages
#define PLOT_FAIL_MSG "Error: Failed to plot benchmark results in subprocess."
#define PLOT_CREATE_MSG "Benchmark Results created in leibniz-benchmark/plots."


void plotBenchmark() {
     static const char* args[] = {PLOT_PRGRM_NAME, PLOT_PRGRM_PATH, NULL}; // Init args to run plotting program
     SubprocessErr err; // Holds err for subprocesses

     int runOutput = subprocessRun(PLOT_PRGRM_NAME, args, &err); // Execute plotting program

     if(err) { // Error running subprocess
          printf("\n%s\n%s\n", PLOT_FAIL_MSG, subprocessErrStr(err));
     } else { // Parse subprocess output to Benchmark Result 
          close(runOutput);
          printf("\n\n%s\n", PLOT_CREATE_MSG);
     }
}