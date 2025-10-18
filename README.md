# Leibniz Cross-Language Benchmark

This project conducts a cross-language benchmark of the Leibniz Series, a mathematical calculation for estimating pi. The same algorithm has been implemented in C, Java, Python, Python with NumPy, JavaScript, and Go. The algorithm used can be optimized further, but this implementation as chosen for its readability, which aids in cross-language consistency. 

## Environment

Due to the multi-language nature of this project, running locally requires many dependencies be installed on your system. Additionally, many of the subprocess executions require programs like python3 and javac to be on your systems path. Because of this, it is highly recommended that a containerized environment be used to run this project. A Dockerfile and cocker-compose.yml is included at the root level of this repository. If you attempt to run this program outside of Docker, be sure you run `make clean` from project root before building or running the container. 

### Running with Docker

When running this program with the included container, Docker becomes the only system requirement, as the container will handled all other dependencies. The container can be initially built with `docker-compose build` from the project-root directory. Note that this can take upwards of twenty minutes on some systems. However, this command only needs executed once. After the container has finished building, the benchmark can be repeatedly run with `docker-compose --rm run run_benchmark [options]`. 