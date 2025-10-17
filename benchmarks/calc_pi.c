#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>


#define WARM_UP_N 1000


double calcPi(int nTerms) {
    double pi = 0.0;

    for(int i = 0; i < nTerms; i++) {
        int sign = 1;

        if(i % 2 == 1)
            sign = -1;

        pi += sign / (2.0 * i + 1);
    }

    return 4 * pi;
}

void runBenchmark(int nTerms) {
    calcPi(WARM_UP_N); // Warm up for caching, branch prediction, etc.

    // Declare vars for benchmark timing
    struct timespec wallStart, wallEnd;
    clock_t cpuStart, cpuEnd;

    // Start timing
    clock_gettime(CLOCK_MONOTONIC, &wallStart);
    cpuStart = clock();

    double res = calcPi(nTerms); // Run benchmark

    // End timing
    cpuEnd = clock();
    clock_gettime(CLOCK_MONOTONIC, &wallEnd);

    // Calculate wall-clock time
    double wallTime = (wallEnd.tv_sec - wallStart.tv_sec) +
                       (wallEnd.tv_nsec - wallStart.tv_nsec) / 1e9;

    // Calculate CPU time
    double cpuTime = (double)(cpuEnd - cpuStart) / CLOCKS_PER_SEC;

    printf("%lf %lf %lf", wallTime, cpuTime, res);
}

int main(int argc, char* argv[]) {
    if(argc < 2) { // nTerms arg missing
        printf("\nnTerms arg missing");
        return 1;
    }

    char* endptr; // Points to end of arg conversion
    long nTerms = strtol(argv[1], &endptr, 10); // Convert arg to long
    
    if(*endptr != '\0') { // Error converting nTerms to numerical val
        printf("\nnTerms could not be parsed: \"%s\"", argv[1]);
        return 2; // Non-valid int passed
    }

    if (nTerms < INT_MIN || nTerms > INT_MAX) { // nTerms outside of valid range
        printf("\nnTerms arg out of valid int range");
        return 3;
    }

    runBenchmark((int)nTerms); // Run benchmark

    return 0;
}