#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tests.h"

#define NUM_TESTS 7
#define MAX_ARGS 6

static char* duplicateString(const char* src) {
    char* dst = malloc(strlen(src) + 1);
    if (dst) strcpy(dst, src);
    return dst;
}

static char* intToString(int num) {
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", num);
    return duplicateString(buffer);
}

Test** getTests(int nTerms, int* numTests) {
    *numTests = NUM_TESTS;

    // Static template test definitions
    static const char* pyTemplate[] = {"python3", "benchmarks/calc_pi.py", NULL, NULL};
    static const char* javaTemplate[] = {"java", "-cp", "benchmarks/bin", "benchmarks.CalcPi", NULL, NULL};
    static const char* cTemplate[] = {"./benchmarks/bin/calc_pi", NULL, NULL};
    static const char* c1Template[] = {"./benchmarks/bin/calc_pi_1", NULL, NULL};
    static const char* c2Template[] = {"./benchmarks/bin/calc_pi_2", NULL, NULL};
    static const char* c3Template[] = {"./benchmarks/bin/calc_pi_3", NULL, NULL};
    static const char* jsTemplate[] = {"node", "benchmarks/calc_pi.js", NULL, NULL};

    const char** templates[NUM_TESTS] = {
        pyTemplate, javaTemplate, cTemplate, c1Template, c2Template, c3Template, jsTemplate
    };

    const char* names[NUM_TESTS] = {
        "Python Benchmark",
        "Java Benchmark",
        "C Benchmark",
        "C Benchmark -O1",
        "C Benchmark -O2",
        "C Benchmark -O3",
        "JavaScript Benchmark"
    };

    const char* execPaths[NUM_TESTS] = {
        "python3",
        "java",
        "./benchmarks/bin/calc_pi",
        "./benchmarks/bin/calc_pi_1",
        "./benchmarks/bin/calc_pi_2",
        "./benchmarks/bin/calc_pi_3",
        "node",
    };

    // Allocate array of test pointers
    Test** tests = malloc((NUM_TESTS + 1) * sizeof(Test*));
    tests[NUM_TESTS] = NULL; // NULL-terminate

    char* termStr = intToString(nTerms);

    for (int i = 0; i < NUM_TESTS; i++) {
        // Allocate Test
        Test* t = malloc(sizeof(Test));
        t->name = names[i];
        t->exec_path = execPaths[i];

        // Count args
        int argc = 0;
        while (templates[i][argc] != NULL) argc++;

        // Allocate args array (+2 for termStr and NULL)
        char** args = malloc((argc + 2) * sizeof(char*));

        for(int j = 0; j < argc; j++)
            args[j] = duplicateString(templates[i][j]);

        // Insert termStr before NULL
        args[argc] = duplicateString(termStr);
        args[argc + 1] = NULL;

        t->args = args;
        tests[i] = t;
    }

    free(termStr);
    return tests;
}

void freeTests(Test** tests) {
    for (int i = 0; tests[i] != NULL; i++) {
        char* const* args = tests[i]->args;

        for (int j = 0; args[j] != NULL; j++)
            free(args[j]);
        
        free((void*)args);
        free(tests[i]);
    }
    free(tests);
}