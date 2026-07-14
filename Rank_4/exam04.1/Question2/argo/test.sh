clear
cc -Wall -Wextra -Werror main.c argo.c argo_utils.c -o argo



test()
{
    separator="_______________________"
    echo $separator
    test_string=$1
    echo $test_string > ./input.txt
    echo TEST CASE: $test_string
    echo -n "ARGO PRINTED: "
    ./argo ./input.txt
    main_return=$?
    echo -n "MAIN_RETURNED: "
    if [ $main_return -eq 0 ]; then
        echo "correct"
    else
        echo "error"
    fi
    echo $separator
}

# note:
# special test cases:
# {:12} -> must return -1 and not print anything
# {a:12} -> must return -1 and not print anything
# 1\n
# I think in general, if there is a newline left after getting a valid json from the parser no error should be thrown

# tests from subject
test '1'
test '"bonjour"'
test '"escape! \" "'
clear
test '{"tomatoes":42,"potatoes":234}'
test '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}'
test '"unfinished string'
test '"unfinished string 2\"'
test '{"no value?":}'

# likely first test case in exam
test "1\n"
test "0\n"
test "-1\n"
test "213213\n"
test "2313213\n"
test "--\n"
test "--1\n"
test '"HELLO WORLD"'
test '""'
test '"HELLO WORLD'
# likely tenth test case in exam
test {:42}
# likely fourtenth test case in exam
test {a:42}
test '{"1":"","1":"1","1":"2"}'
test '{"":"","":"","":""}'
test '{"1":"1","2":"2","3":{"11":11,"22":22,"33":{"111":111}}}'

valgrind ./argo input.txt