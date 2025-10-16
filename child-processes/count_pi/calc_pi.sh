#!/bin/bash

# Check if argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <number_of_iterations>"
    exit 1
fi

n=$1
pi=0

for (( k=0; k<n; k++ ))
do
    term=$(echo "scale=10; ((-1)^$k) / (2 * $k + 1)" | bc -l)
    pi=$(echo "scale=10; $pi + $term" | bc -l)
done

pi=$(echo "scale=10; 4 * $pi" | bc -l)

echo "Estimate of pi after $n iterations: $pi"