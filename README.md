# Leibniz Cross-Language Benchmark

This project conducts a cross-language benchmark of the Leibniz Series, a mathematical calculation for estimating pi. The same algorithm has been implemented in C, Java, Python, Python with NumPy, JavaScript, and Go. The algorithm used can be optimized further, but this implementation as chosen for its readability, which aids in cross-language consistency. This is a casual benchmark, which may not provide an accurate representations of a languages performance.  

## Environment

Due to the multi-language nature of this project, running locally requires many dependencies be installed on your system. Additionally, many of the subprocess executions require programs like python3 and javac to be on your systems path. Because of this, it is highly recommended that a containerized environment be used to run this project. A Dockerfile and docker-compose.yml is included at the root level of this repository. If you attempt to run this program outside of Docker, be sure you run `make clean` from project root before building or running the container. 

### Running with Docker

When running this program with the included container, Docker becomes the only system requirement, as the container will handled all other dependencies. The container can be initially built with `docker-compose build` from the project-root directory. Note that this can take upwards of thirty minutes on some systems. However, this command only needs executed once. After the container has finished building, the benchmark can be repeatedly run with `docker-compose --rm run run_benchmark [options]` without needing to rebuild the container. 

# Project Design

## Introduction

## Implementation

The implementation of the `subprocess.c` and `subprocess.h` files in this codebase are designed to provide an abstraction for subprocess execution. The abstraction aims to allow users of this code to only worry about what their subprocesses should do, not how they are executed. It also provides an easy way for callers to detect any errors that occurred, as well as read stdout from the subprocess, facilitating a straightforward communication process.

### Subprocess Interface

The interface provided by `subprocess.h` is intentionally slim, with only two functions and a single Enum. The most important function declared in this file is `int subprocessRun(const char* exec_path, char* const* args, SubprocessErr* err);`, which allows execution of a subprocess. The first parameter, `exec_path`, provides the path to the executable binary to be invoked. When `execvp()` is invoked, the `exec_path` argument defines which process image should replace the original child process image, which is copied from the parent process when `fork()` is invoked.  The second parameter, `args`, is a null-terminated array of arguments to be passed to the new program. Finally, the `err` parameter is a reference to an enum, which is set in the function's execution process to inform caller of success or failure status. 

`subprocessRun` returns an integer file descriptor. allowing callers to read stdout the child process. Unix systems Associate a small integer with any open file within a process, which provides the basis of the `pipe` function. in `subprocessRun`, a 2-element array of file descriptors is initialized. When passed as argument to the `pipe` function, the kernel creates a temporary file in the kernels working memory, and initializes the elements in the array. Index zero will hold the file descriptor that allows reading of the kernel-file, while index one provides write-access. Then, after the child process is created but before swapping the process image, the `dup2` function is used to redirect the child processes stdout to the write end of the pipe. Thus, the parent process is able to directly read the bytes written to stdout during execution of the subprocess. 

Regardless of whether the caller code actually reads the subprocess output, It is essentially that they close the read end of the pipe. Failure to do so will cause a memory leak. Additionally, because pipes are stored in kernel memory, which is shared between processes, the system strain will affect outside processes more than a user-space memory leak would. Additionally, the kernel will not automatically free the resource until both the child and the parent processes have either closed their end of the pipe or terminated.



## Results

### Process Creation and Management

### Parent and Child Process Interactions

## Conclusion