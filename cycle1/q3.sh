#!/bin/bash

# Check if a file is provided as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <glossary_file>"
    exit 1
fi

# Check if the file exists
if [ ! -f "$1" ]; then
    echo "Error: File '$1' not found!"
    exit 1
fi

# Read the file into an array
mapfile -t lines < "$1"

# Print the array in reverse order
for (( i=${#lines[@]}-1; i>=0; i-- )); do
    echo "${lines[i]}"
done
