#!/bin/sh

# pip3 install --no-cache-dir -r requirements.txt # Install Python dependencies
make # Compile if needed
./bin/run "$@" # Run program with args
