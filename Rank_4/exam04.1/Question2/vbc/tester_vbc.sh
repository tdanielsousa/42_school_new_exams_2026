!/bin/bash

echo "This script is used to test the VBC calculator"

rm output_expected.txt output_actual.txt

# ANSI escape codes for colors
RED='\033[0;31m'
NC='\033[0m' # No Color

#function to compare output of program and bash
check_diff() {
    diff "$1" "$2" > diff_file
    if [ -s "diff_file" ]; then
        echo "File is not empty. Failed"
        cat "diff_file"
    else
        echo "File is empty. Success"
    fi
}

# Path to the parser executable
VBC=./vbc

#create two files for output
touch output_expected.txt output_actual.txt

# Test 1