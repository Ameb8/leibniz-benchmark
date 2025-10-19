#include <stdio.h>
#include <stdlib.h>

#include "../include/tests.h"
#include "../include/benchmark.h"

#define NTERM 1000000
#define NUM_RUNS 10
#define DATA_FILE_NAME "benchmark_dat/results.csv"
#define DATA_FILE_LBL "Benchmark,Wall-Clock Time,CPU Time,Pi Result\n"


BenchmarkResult** runBenchmarks() {
     // Open file for data writing
     FILE* benchmarkData = fopen(DATA_FILE_NAME, "w");
     
     if(!benchmarkData) // File failed to open
          return NULL;

     fprintf(benchmarkData, DATA_FILE_LBL); // Write data label

     // Get test cases
     int numTests;
     const Test** tests = getTests(NTERM, &numTests);

     for(int i = 0; i < numTests; i++) { // Run all test cases
          for(int j = 0; j < NUM_RUNS; j++) {
               BenchmarkResult* result = benchmarkRun(tests[i]); // Execute benchmark
          
               if(!result) { // Benchmark execution or processing failed
                    printf("\n\n\nTest '%s' Failed", tests[i]->name);
               } else { // Display benchmark results
                    printf("\n\n\nTest '%s':", tests[i]->name);
                    benchmarkPrint(result);

                    fprintf( // Write run result to file
                         benchmarkData, 
                         "%s,%lf,%lf,%lf\n", 
                         tests[i]->name, 
                         result->clockTime, 
                         result->cpuTime, 
                         result->piEstimate
                    );
               }
          }
     }

     freeTests(tests);
     return NULL;
}

void createGraphics();

int main() {
     // testSubprocess();
     runBenchmarks();
     createGraphics();
     
}