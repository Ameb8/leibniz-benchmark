#include <stdio.h>

#include "../include/tests.h"

#define NUM_TESTS 5

// Define Java test
static char *const java_args[] = {"java", "-cp", "benchmarks/bin", "benchmarks.CalcPi", "1000000000", NULL};
static const Test JAVA_TEST = {
    .name = "Java Benchmark",
    .exec_path = "java",
    .args = java_args
};

// C benchmark
static char *const c_args[] = {"./benchmarks/bin/calc_pi", "1000000000", NULL};
static const Test C_TEST = {
    .name = "C Benchmark",
    .exec_path = "./benchmarks/bin/calc_pi",
    .args = c_args
};

static char *const c_args_1[] = {"./benchmarks/bin/calc_pi_1", "1000000000", NULL};
static const Test C_TEST_1 = {
    .name = "C Benchmark -O1",
    .exec_path = "./benchmarks/bin/calc_pi_1",
    .args = c_args_1
};

static char *const c_args_2[] = {"./benchmarks/bin/calc_pi_2", "1000000000", NULL};
static const Test C_TEST_2 = {
    .name = "C Benchmark -O2",
    .exec_path = "./benchmarks/bin/calc_pi_2",
    .args = c_args_2
};

static char *const c_args_3[] = {"./benchmarks/bin/calc_pi_3", "1000000000", NULL};
static const Test C_TEST_3 = {
    .name = "C Benchmark -O3",
    .exec_path = "./benchmarks/bin/calc_pi_3",
    .args = c_args_3
};
/*
// Python Benchmark
static char *const python_args[] = {"python3", "child-processes/count_pi/calc_pi.py", NULL};
static const Test PYTHON_TEST = {
    .name = "Python Benchmark",
    .exec_path = "python3",
    .args = python_args
};

// NULL-terminated array of test pointers
const Test* TESTS[] = {
    &JAVA_TEST,
    &C_TEST,
    &PYTHON_TEST,
    NULL // Sentinel to mark end
};
*/

const Test* TESTS[] = {
    &JAVA_TEST,
    &C_TEST,
    &C_TEST_1,
    &C_TEST_2,
    &C_TEST_3,
    NULL
};

const Test** get_tests(int* numTests) {
    *numTests = NUM_TESTS;
    return TESTS;
}