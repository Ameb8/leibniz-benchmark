#ifndef BENCHMARK_H
#define BENCHMARK_H


#include "tests.h"


typedef struct {
    double cpuTime;
    double clockTime;
    double piEstimate;
} BenchmarkResult;


BenchmarkResult* execBenchmark(Test* test);

#endif