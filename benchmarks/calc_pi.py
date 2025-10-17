import time
import sys
import numpy as np

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

def run_benchmark(n_terms: int) -> None:
    for i in range(10): # Warmup Python environment
        calc_pi(10000)

    # Start timings
    start_wall: float = time.time()
    start_cpu: float = time.process_time()

    pi = calc_pi(n_terms) # Run benchmark

    # End timings
    end_cpu: float = time.process_time()
    end_wall: float = time.time()

    # Output results
    print(f"{end_wall - start_wall:.6f} {end_cpu - start_cpu:.6f} {pi}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Please provide the number of terms as a command-line argument.")
        sys.exit(1)

    try:
        n_terms = int(sys.argv[1])
    except ValueError:
        print(f"Invalid number format: {sys.argv[1]}")
        sys.exit(1)

    # run_benchmark(n_terms)
    run_benchmark(n_terms)