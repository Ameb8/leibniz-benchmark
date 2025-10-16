#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#include "../include/benchmark.h"


#define BUF_SIZE 20


BenchmarkResult* execBenchmark(Test* test) {
    int pipefd[2]; // Pipe to receive output from benchmark subprocess
    pid_t pid; // ID of benchmark process

    if(pipe(pipefd) == -1)   // Error creating pipe
        return NULL;

    pid = fork(); // Create subprocess

    if(pid < 0) // Error creating subprocess;
        return NULL;

    if(pid == 0) { // Child process
        close(pipefd[0]); // Close read end of stdout on child process
        
        if(dup2(pipefd[1], STDOUT_FILENO) == -1) // Redirect child's stdout to pipe
            return NULL; // Error redirecting stdout
        
        close(pipefd[1]); // Close original pipe
        
        // Execute program

        return NULL; //Error occurred, exec should not return
    } else { // Parent process
        close(pipefd[1]); // Close write end of pipe

        int status;
        waitpid(pid, &status, 0);

        // Get result
        BenchmarkResult* result = parseOutput(pipefd[0]);
        close(pipefd[0]); // Close pipe

        return result;
    }

    return NULL;
}

BenchmarkResult* parseResult(int fd) {
    size_t total_read = 0;
    ssize_t bytes_read;
    char buffer[BUF_SIZE];

    while (total_read < BUF_SIZE - 1) { 
        // Read data from fd
        bytes_read = read(fd, buffer + total_read, BUF_SIZE - 1 - total_read)
    
        
    }
}