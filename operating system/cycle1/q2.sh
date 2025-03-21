#!/bin/bash

# Initialize counters
line_count=0
word_count=0
char_count=0

# Read input line by line
while IFS= read -r line; do
    ((line_count++))
    
    # Count characters (including spaces)
    char_count=$((char_count + ${#line}))
    
    # Count words
    for word in $line; do
        ((word_count++))
    done
done

echo "Lines: $line_count"
echo "Words: $word_count"
echo "Characters: $char_count"
