#!/bin/bash

echo "This script is used to test the JSON parser"

cc -Wall -Wextra -Werror main.c argo.c argo_utils.c -o argo

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

check_return(int i, int j) {
	if [ i == j]; then
		echo "Return value is correct"
	else
		echo "Return value is not correct"
	fi
}

# Path to the parser executable
ARGO=./argo

#create two files for output
touch output_expected.txt output_actual.txt

# Test 1
echo "Test 1: Parsing a number"
echo 'Expected: 1'
echo -n '1' | $ARGO /dev/stdin > output_actual.txt
echo '1' > output_expected.txt
check_diff output_expected.txt output_actual.txt

# Test 2
echo "Test 2: Parsing a string"
echo 'Expected: "bonjour"'
echo -n '"bonjour"' | $ARGO /dev/stdin > output_actual.txt
echo '"bonjour"' > output_expected.txt
check_diff output_expected.txt output_actual.txt

# Test 3
echo "Test 3: Parsing escape symbol for quotation marks"
echo: 'Expected: "escape! \" "'
echo -n '"escape! \" "' | $ARGO /dev/stdin > output_actual.txt
echo '"escape! \" "' > output_expected.txt
check_diff output_expected.txt output_actual.txt

# Test 4
echo "Parsing escape symbol for backslashes"
echo 'Expected: "escape! \ "'
echo -n '"escape! \\ "' | $ARGO /dev/stdin > output_actual.txt
echo '"escape! \\ "' > output_expected.txt
check_diff output_expected.txt output_actual.txt

# Test 5
echo "Parsing maps"
echo 'Expected: {"tomatoes":42,"potatoes":234}'
echo -n '{"tomatoes":42,"potatoes":234}' | $ARGO /dev/stdin > oytput_actaul.txt
echo '{"tomatoes":42,"potatoes":234}' > output_expected.txt
check_diff output_expected.txt output_actual.txt

#Test 6
echo "Parsing nested maps"
echo 'Expected {"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}'
echo -n  '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' | $ARGO /dev/stdin > output_actual.txt
echo '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' > output_expected.txt
check_diff output_expected.txt output_actual.txt

#Test 7
echo "Parsing unfinished string"
echo 'Expected: unexpected end of input'
echo -n '"unfinished string' | $ARGO /dev/stdin > output_actual.txt
echo 'unexpected end of input' > output_expected.txt
check_diff output_expected.txt output_actual.txt

#Test 8
echo "Parsing unexpected token space"
echo "Expected: unexpected token ' '"
echo -n echo "\"key\"   :   \"value\"" | $ARGO /dev/stdin > output_actual.txt
check_diff output_expected.txt output_actual.txt

#Test 9
echo "Parsing unexpected token EOF"
echo 'Expected: unexpected end of input'
echo -n '"unfinished string 2\"' | $ARGO /dev/stdin
echo 'unexpected end of input' > output_expected.txt
check_diff output_expected.txt output_actual.txt

#Test 10
echo "Parsing invalid escape sequences"
echo "Expected: unexpected token 'q'" > output_expected.txt
echo "\"invalid escape \\q\"" | $ARGO /dev/stdin > output_actual.txt
check_diff output_expected.txt output_actual.txt

#Test 11
echo "Parsing unexpected braces/brackets in objects"













