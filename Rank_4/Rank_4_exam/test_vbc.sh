#!/bin/bash

# compile:
gcc -Wall -Wextra -Werror *.c -o vbc

echo "--- standard TESTS: ---"
./vbc '1'
./vbc '2+3'
./vbc '3*4+5'
./vbc '3+4*5'
./vbc '(3+4)*5'
./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2'

echo -e "\n--- Error TESTS ---"
./vbc '1+'          # we expect: Unexpected end of input
./vbc '1+2)'        # we expect: Unexpected token ')'
./vbc '((1+3)*12'   # we expect: Unexpected token '2' (так как 12 - это два числа подряд)
./vbc '(1+2'        # we expect: Unexpected end of input

echo -e "\n--- difficult TEST ---"
./vbc '((6*6+7+5+8)*(1+0+4*8+7)+2)+4*(1+2)' # we expect: 2254
