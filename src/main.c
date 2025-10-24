#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/tests.h"
#include "../include/benchmark.h"
#include "../include/subprocess.h"


#define NTERM 1000000
#define NUM_RUNS 10
#define DATA_FILE_NAME "benchmark_dat/results.csv"
#define DATA_FILE_LBL "Benchmark,Wall-Clock Time,CPU Time,Pi Result\n"
#define PLOT_PRGRM_PATH "benchmark_results/plot_benchmark.py"
#define PLOT_PRGRM_NAME "python3"
#define PLOT_FAIL_MSG "Error: Failed to plot benchmark results in subprocess."
#define PLOT_CREATE_MSG "Benchmark Results created in leibniz-benchmark/plots."
#define TEST_SUBPRCS_NAME "bash"
#define TEST_SUBPRCS_FLAG "-c"
#define TEST_SUBPRCS_CMD "echo 'Alex'"
#define TEST_SUBPRCS_ERR_MSG "Error: Subprocess for echo command failed to execute."
#define TEST_SUBPRCS_SCS_MSG "'Echo' command successfully executed as subprocess"

#define HELP_MSG "Help Message Placeholder"



void printProgressBar(int current, int total) {
    int barWidth = 50;
    float progress = (float)current / total;
    int pos = barWidth * progress;

    printf("\r[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %3d%%", (int)(progress * 100));
    fflush(stdout);
}



BenchmarkResult** runBenchmarks(int nTerm, int numRuns) {
     // Open file for data writing
     FILE* benchmarkData = fopen(DATA_FILE_NAME, "w");
     
     if(!benchmarkData) // File failed to open
          return NULL;

     fprintf(benchmarkData, DATA_FILE_LBL); // Write data label

     // Get test cases
     int numTests;
     const Test** tests = getTests(nTerm, &numTests);

     for(int i = 0; i < numTests; i++) { // Run all test cases
          printf("\n\nRunning %d iterations of %s as subprocesses\n", NUM_RUNS,  tests[i]->name);
          for(int j = 0; j < numRuns; j++) {
               BenchmarkResult* result = benchmarkRun(tests[i]); // Execute benchmark
          
               if(!result) { // Benchmark execution or processing failed
                    printf("\n\n\nTest '%s' Failed", tests[i]->name);
               } else { // Display benchmark results
                    fprintf( // Write run result to file
                         benchmarkData, 
                         "%s,%lf,%lf,%lf\n", 
                         tests[i]->name, 
                         result->clockTime, 
                         result->cpuTime, 
                         result->piEstimate
                    );
               }

               printProgressBar(j + 1, numRuns);
          }
     }

     fclose(benchmarkData);
     freeTests(tests);
     return NULL;
}

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
                    printf("\n%s\n", HELP_MSG);
                    return false;
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
          runBenchmarks(nTerm, numRuns);
          createGraphics();
     }

     return 0;
}