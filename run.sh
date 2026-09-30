#!/bin/bash
# Usage: ./run.sh <file.cpp> [input_file | tests_dir]

FILE=${1:?"Usage: ./run.sh <file.cpp> [input_file | tests_dir]"}
BIN="${FILE%.cpp}"

g++-15 -std=c++17 -O2 -Wall -o "$BIN" "$FILE" || exit 1

if [ -d "$2" ]; then
    for f in "$2"/*.txt; do
        echo "== $f"
        ./"$BIN" < "$f"
    done
elif [ -n "$2" ]; then
    time ./"$BIN" < "$2"
else
    time ./"$BIN"
fi
