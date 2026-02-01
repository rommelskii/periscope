#!/bin/bash

#Build project first
./build.sh
cd bin

for test_file in ./test_*; do
    if [ -x "$test_file" ]; then
        echo "Running: $test_file"
        "$test_file"
    else
        echo "Skipping: $test_file (not executable)"
    fi
done
