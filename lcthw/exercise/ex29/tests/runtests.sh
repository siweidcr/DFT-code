echo "Running unit tests:"

for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so print_a_message "hello there" 15 >> tests/tests.log
        then
            echo $i 1 PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done
for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so uppercase "hello there" 15 >> tests/tests.log
        then
            echo $i 2 PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done
for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so lowercase "HeLLo tHeRe" 15 >> tests/tests.log
        then
            echo $i 3 PASS
        else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
        fi
    fi
done
for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i ./build/libYOUR_LIBRARY.so fail_on_purpose "i fail" 15 >> tests/tests.log
        then
	    echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
            
        else
            echo $i 4 PASS 
        fi
    fi
done

echo "##test######"
