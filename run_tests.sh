#!/bin/bash

#complies the driver.cpp and matmul.cpp file
g++ -o driver driver.cpp matmul.cpp -std=c++14

#checks if the previous command is executed successfully
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
else
    echo "Compilation failed!"
    exit 1
fi

echo "Running the Unit Tests..."

#executes the driver file
./driver


if [ -f "./result.csv" ]; then
    echo "Unit Tests completed. Results stored in result.csv."
else
    echo "Error: result.csv not generated."
fi

