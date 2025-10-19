#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../include/benchmark.h"

#include "../include/subprocess.h"
#include "../include/debug_log.h"


BenchmarkResult* parseResult(int fd);
BenchmarkResult* initBenchmark(char* benchmarkData);


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