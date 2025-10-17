import time
import sys
import numpy as np
from typing import Callable

def calc_pi(n_terms: int) -> float:
    pi: float = 0.0

    for i in range(n_terms):
        sign: int = 1

        if i % 2 == 1:
            sign = -1

        pi += sign / (2.0 * i + 1)
    
    return 4 * pi

def calc_pi_numpy(n_terms: int) -> float:
    i = np.arange(n_terms)
    signs = (-1) ** i
    denominators = 2 * i + 1
    terms = signs / denominators
    pi = 4 * np.sum(terms)
    return pi

def run_benchmark(n_terms: int, use_np: bool) -> None:
    # Assign correct benchmark function
    calc_func: Callable[[int], float] = calc_pi

    if use_np: # Benchmark numpy implementation
        calc_func = calc_pi_numpy

    for i in range(10): # Warmup Python environment
        calc_func(10000)

    # Start timings
    start_wall: float = time.time()
    start_cpu: float = time.process_time()

    pi = calc_func(n_terms) # Run benchmark

    # End timings
    end_cpu: float = time.process_time()
    end_wall: float = time.time()

    # Output results
    print(f"{end_wall - start_wall:.6f} {end_cpu - start_cpu:.6f} {pi}")


if __name__ == "__main__":
    if len(sys.argv) < 2: # Not enough args
        print("Usage: python calc_pi.py [-np] <number_of_terms>")
        sys.exit(1)

    use_np = False
    arg_index = 1

    # Check if first argument is '-np'
    if sys.argv[arg_index] == "-np":
        use_np = True
        arg_index += 1

    # Parse n_terms from the next arg
    if arg_index >= len(sys.argv):
        print("Please provide the number of terms as a command-line argument.")
        sys.exit(1)

    try: # Attempt to parse n_terms arg
        n_terms = int(sys.argv[arg_index])
    except ValueError: # Invalid n_terms arg
        print(f"Invalid number format: {sys.argv[arg_index]}")
        sys.exit(1)

    run_benchmark(n_terms, use_np) # Run benchmark
