#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../include/benchmark.h"

#include "../include/subprocess.h"
#include "../include/debug_log.h"


typedef struct {
    double cpuTime;
    double clockTime;
    double piEstimate;
} BenchmarkResult;


#define BUF_SIZE 60


BenchmarkResult* benchmarkInit(char* benchmarkData) {
    BenchmarkResult* result = malloc(sizeof(BenchmarkResult)); // Allocate result mem

    if(!result) // Error instantiating result
        return NULL;

    // Read float data into result
    int parsed = sscanf(
        benchmarkData,
        "%lf %lf %lf",
        &(result->clockTime),
        &(result->cpuTime),
        &(result->piEstimate)
    );

    if(parsed != 3) { // Error reading results
        DEBUG_LOG("\nError reading floats from: \"%s\"", benchmarkData);
        free(result);
        return NULL;
    }

    return result;
}



BenchmarkResult* benchmarkParse(int fd) {
    size_t total_read = 0;
    ssize_t bytes_read;
    char buffer[BUF_SIZE];

    while (total_read < BUF_SIZE - 1) { 
        // Read data from fd
        bytes_read = read(fd, buffer + total_read, BUF_SIZE - 1 - total_read);
    
        if (bytes_read == 0) { // End of data read
            break;
        } else if(bytes_read < 0) { // Read error
            DEBUG_LOG("\nError reading from pipe");
            return NULL;
        }

        total_read += bytes_read; // Increment bytes read
    }

    buffer[total_read] = '\0';
    
    return benchmarkInit(buffer);
}


BenchmarkResult* benchmarkRun(const Test* test) {
    BenchmarkResult* res = NULL;
    SubprocessErr err;

    int run_output = subprocessRun(test->exec_path, test->args, &err); // Run benchmark

    if(err) { // Error running subprocess
        printf("\n%s", subprocessErrStr(err));
    } else { // Parse subprocess output to BenchmarkResult
        res = benchmarkParse(run_output);
        close(run_output);
    }

    return res;
}

void benchmarkPrint(BenchmarkResult* result) {
    printf( // Print Results
        "\nClock Time: %lf\nCPU Time: %lf\nPi Result: %lf", 
        result->clockTime, 
        result->cpuTime, 
        result->piEstimate
    );
}

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

void writeResult(FILE* resultsFile, char* testName, BenchmarkResult* result) {
    fprintf( // Write run result to file
            resultsFile, 
            "%s,%lf,%lf,%lf\n", 
            testName, 
            result->clockTime, 
            result->cpuTime, 
            result->piEstimate
    );
}


void runBenchmarks(int nTerm, int numRuns, char* dataName, char* dataLabel) {
     // Open file for data writing
     FILE* benchmarkData = fopen(dataName, "w");
     
     if(!benchmarkData) // File failed to open
          return;

     fprintf(benchmarkData, dataLabel); // Write data label

     // Get test cases
     int numTests;
     const Test** tests = getTests(nTerm, &numTests);

     for(int i = 0; i < numTests; i++) { // Run all test cases
          printf("\n\nRunning %d iterations of %s as subprocesses\n", numRuns,  tests[i]->name);
          for(int j = 0; j < numRuns; j++) {
               BenchmarkResult* result = benchmarkRun(tests[i]); // Execute benchmark
          
               if(!result) // Benchmark execution or processing failed
                    printf("\n\n\nTest '%s' Failed", tests[i]->name);
               else // Save benchmark results
                    writeResult(benchmarkData, tests[i]->name, result);

               printProgressBar(j + 1, numRuns);
          }
     }

     fclose(benchmarkData);
     freeTests(tests);
}

