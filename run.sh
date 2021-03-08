#!/usr/bin/env bash
g++ build.cpp -o build
g++ process.cpp -o process
./build 0 24 $1 24 0 obstacles.txt
../minisat input.txt output.txt
./process $1 output.txt trajectory.txt
cat trajectory.txt
