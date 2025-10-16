#include <stdio.h>
#include <stdlib.h>

#include "../include/tests.h"
#include "../include/benchmark.h"


BenchmarkResult** runBenchmarks() {
     // Get test cases
     int num_tests;
     const Test** tests = get_tests(&num_tests);

     for(int i = 0; i < num_tests; i++) { // Run all test cases
          BenchmarkResult* result = execBenchmark(tests[i]); // Execute benchmark
     
          if(!result) { // Benchmark execution or processing failed
               printf("\n\n\nTest '%s' Failed", tests[i]->name);
          } else { // Display benchmark results
               printf("\n\n\nTest '%s':", result);
               benchmarkPrint(result);
          }
     }

     return NULL;
}

int main() {
     runBenchmarks();
}