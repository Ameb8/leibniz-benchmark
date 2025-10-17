#include <stdio.h>

#include "../include/tests.h"

#define NUM_TESTS 6

// Define Java test
static char *const java_args[] = {"java", "-cp", "benchmarks/bin", "benchmarks.CalcPi", "10000000", NULL};
static const Test JAVA_TEST = {
    .name = "Java Benchmark",
    .exec_path = "java",
    .args = java_args
};

// C benchmark
static char *const c_args[] = {"./benchmarks/bin/calc_pi", "10000000", NULL};
static const Test C_TEST = {
    .name = "C Benchmark",
    .exec_path = "./benchmarks/bin/calc_pi",
    .args = c_args
};

static char *const c_args_1[] = {"./benchmarks/bin/calc_pi_1", "10000000", NULL};
static const Test C_TEST_1 = {
    .name = "C Benchmark -O1",
    .exec_path = "./benchmarks/bin/calc_pi_1",
    .args = c_args_1
};

static char *const c_args_2[] = {"./benchmarks/bin/calc_pi_2", "10000000", NULL};
static const Test C_TEST_2 = {
    .name = "C Benchmark -O2",
    .exec_path = "./benchmarks/bin/calc_pi_2",
    .args = c_args_2
};

static char *const c_args_3[] = {"./benchmarks/bin/calc_pi_3", "10000000", NULL};
static const Test C_TEST_3 = {
    .name = "C Benchmark -O3",
    .exec_path = "./benchmarks/bin/calc_pi_3",
    .args = c_args_3
};

// Python Benchmark
static char *const py_args[] = {"python3", "benchmarks/calc_pi.py", "10000000", NULL};
static const Test PY_TEST = {
    .name = "Python Benchmark",
    .exec_path = "python3",
    .args = py_args
};

// NULL-terminated array of test pointers
const Test* TESTS[] = {
    &JAVA_TEST,
    &C_TEST,
    &C_TEST_1,
    &C_TEST_2,
    &C_TEST_3,
    &PY_TEST,
    NULL
};

const Test** get_tests(int* numTests) {
    *numTests = NUM_TESTS;
    return TESTS;
}