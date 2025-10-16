#include <stdio.h>

#include "../include/tests.h"

// Define Java test
static char *const java_args[] = {"java", "CalcPi", NULL};
static const Test JAVA_TEST = {
    .name = "Java Benchmark",
    .exec_path = "java",
    .args = java_args
};

// C benchmark
static char *const c_args[] = {"./calc_pi.c", NULL};
static const Test C_TEST = {
    .name = "C Benchmark",
    .exec_path = "./calc_pi.c",
    .args = c_args
};

// Python Benchmark
static char *const python_args[] = {"python3", "calc_pi.py", NULL};
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

const Test** get_tests(void) {
    return TESTS;
}