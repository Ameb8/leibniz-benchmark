#ifndef BENCHMARK_H
#define BENCHMARK_H


#include "tests.h"


typedef struct {
    double cpuTime;
    double clockTime;
    double piEstimate;
} BenchmarkResult;


BenchmarkResult* benchmarkRun(const Test* test);
void benchmarkPrint(BenchmarkResult* result);

#endif