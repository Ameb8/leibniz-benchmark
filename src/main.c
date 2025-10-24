#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

 
#include "../include/benchmark.h"
#include "../include/subprocess.h"
#include "../include/config.h"
#include "../include/help.h"



#define PLOT_PRGRM_PATH "benchmark_results/plot_benchmark.py"
#define PLOT_PRGRM_NAME "python3"
#define PLOT_FAIL_MSG "Error: Failed to plot benchmark results in subprocess."
#define PLOT_CREATE_MSG "Benchmark Results created in leibniz-benchmark/plots."
#define TEST_SUBPRCS_NAME "bash"
#define TEST_SUBPRCS_FLAG "-c"
#define TEST_SUBPRCS_CMD "echo 'Alex'"
#define TEST_SUBPRCS_ERR_MSG "Error: Subprocess for echo command failed to execute."
#define TEST_SUBPRCS_SCS_MSG "'Echo' command successfully executed as subprocess"




void testSubprocess() {
     static const char* args[] = {TEST_SUBPRCS_NAME, TEST_SUBPRCS_FLAG, TEST_SUBPRCS_CMD, NULL};
     SubprocessErr err;

     int runOutput = subprocessRun(TEST_SUBPRCS_NAME, args, &err);

     if(err) { // Subprocess execution failed
          printf("\n%s\n%s\n", TEST_SUBPRCS_ERR_MSG, subprocessErrStr(err));
     } else {
          printf("\n%s\n", TEST_SUBPRCS_SCS_MSG);
          close(runOutput);
     }
}

void createGraphics() {
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


bool parseArgs(int argc, char* argv[], int* nTerm, int* numRuns) {
     int opt;
     
     while((opt = getopt(argc, argv, "n:r:")) != -1) {
          switch (opt) {
               case 'n': // Set nterm for leibniz series benchmarks
                    *nTerm = strtol(optarg, NULL, 10);
                    break;     
               case 'r': // Set number of runs for each benchmark
                    *numRuns = strtol(optarg, NULL, 10);
                    break;
               case 'h': // Print help message and return false
                    printHelp();
                    return false;
               default:
                    printUsage();
          }
     }

     return true;
}


int main(int argc, char* argv[]) {
     // Set default test run values
     int nTerm = NTERM;
     int numRuns = NUM_RUNS;

     if(parseArgs(argc, argv, &nTerm, &numRuns)) {
          testSubprocess();
          runBenchmarks(nTerm, numRuns, DATA_FILE_NAME, DATA_FILE_LBL);
          createGraphics();
     }

     return 0;
}