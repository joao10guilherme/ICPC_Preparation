#!/bin/bash
# Usage: ./run.sh <file.cpp> [input_file]

FILE=${1:?"Usage: ./run.sh <file.cpp> [input_file]"}
BIN="${FILE%.cpp}"

g++-15 -std=c++17 -O2 -Wall -o "$BIN" "$FILE" || exit 1

if [ -n "$2" ]; then
    time ./"$BIN" < "$2"
else
    time ./"$BIN"
fi
