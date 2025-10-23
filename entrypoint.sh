#!/bin/sh
set -e

make  # builds all project targets

if [ "$BUILD_TYPE" = "debug" ]; then # Set binary as debug build
  BINARY=./bin/run_debug
else # Set binary as release build
  BINARY=./bin/run
fi

exec $BINARY "$@" # Execute binary with user-provided args