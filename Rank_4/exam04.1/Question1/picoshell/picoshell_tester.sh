#!/bin/bash
echo "Hello"

gcc main.c picoshell_2.c -o pico

check_diff() {
	diff "$1" "$2" > diff_file
	if [ -s "diff_file" ]; then
		echo "File is not empty. Failed"
		cat "diff_file"
	else
		echo "File is empty. Success"
	fi
}

check_return() {
	if [ "$1" == "$2" ]; then
		printf "Return value is %s. Correct.\n" "$1"
	else
		printf "Return value is %s. Expected %s. Error.\n" "$1" "$2"
	fi
}

touch shell_output pico_output diff_file

echo "Test 1: ls"
./pico ls > pico_output
return_pico=$?
ls > shell_output
return_expected=0
check_diff shell_output pico_output
check_return $return_pico $return_expected

echo "Test 2: ls | wc -l"
./pico  ls -l "|" wc -l > pico_output
return_pico=$?
ls -l | wc -l > shell_output
return_expected=0
check_diff shell_output pico_output
check_return $return_pico $return_expected

echo "Test 3: wrong commands"
./pico lsdf "|" wcsaf > pico_output
return_pico=$?
sort lsdf | wcsaf > shell_output
return_expected=0
check_diff shell_output pico_output
check_return $return_pico $return_expected

# Additional Test 1: Simple command with arguments (echo)
echo "Test 4: Simple command with arguments"
./pico echo "Hello" > pico_output
return_pico=$?
echo "Hello" > shell_output
return_expected=0
check_diff shell_output pico_output
check_return $return_pico $return_expected

# Additional Test 2: Pipe between two commands (echo "Hello" | grep "Hello")
echo "Test 5: Pipe between two commands"
./pico echo "Hello" "|" grep "Hello" > pico_output
return_pico=$?
echo "Hello" | grep "Hello" > shell_output
return_expected=0
check_diff shell_output pico_output
check_return $return_pico $return_expected

rm pico_output shell_output pico diff_file

exit 0
