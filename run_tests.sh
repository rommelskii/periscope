#!/bin/bash

# Navigate to your test directory if necessary
cd build && make && cd ../bin

for test_file in ./test_*; do
    if [ -x "$test_file" ]; then
        echo "Running: $test_file"
        "$test_file"
    else
        echo "Skipping: $test_file (not executable)"
    fi
done
