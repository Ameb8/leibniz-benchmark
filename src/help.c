#include <stdio.h>
#include "../include/help.h"

void printHelp(void) {
    printf(
        "\n\nLeibniz Cross-Language Benchmark\n\n"
        "This program benchmarks multiple language implementations of the Leibniz series\n"
        "for approximating π (pi). Each implementation is executed as a subprocess and\n"
        "timed for both wall-clock and CPU performance.\n\n"
        "Options:\n"
        "  -n <int>  Set number of terms (N) in the Leibniz series. Default: 1000000\n"
        "  -r <int>  Set how many times each benchmark runs. Default: 10\n"
        "  -h        Display this help message.\n\n"
        "Example:\n"
        "  ./benchmark -n 500000 -r 5\n\n"
        "Output:\n"
        "  Results saved to benchmark_dat/results.csv\n"
        "  Plots saved to leibniz-benchmark/plots/\n\n"
    );
}

void printUsage(void) {
    printf("\n\nUsage: ./benchmark [-n <num_terms>] [-r <num_runs>] [-h]\n");
}