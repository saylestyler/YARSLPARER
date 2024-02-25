#!/bin/bash

# Target file to write to
file="large_example_file.md"
# Number of lines to write
lines=5120000

echo "Writing $lines lines to $file..."

for ((i=1; i<=lines; i++)); do
    echo "This is line $i" >> "$file"
done

echo "Done writing lines."

