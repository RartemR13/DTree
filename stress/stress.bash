#!/usr/bin/env bash 

test_count=0

for dir in `find ./stress/tests/* -depth -type d`
do
	test_count=$((test_count+1))
done

for (( i=1; i<=${test_count}; i++ ))
do
	touch out
	./stress/stress_test<stress/tests/test${i}/test${i}>out
		
	if cmp -s out stress/tests/test${i}/ans${i}; then
		echo "Stress ${i}: OK"
	else
		echo "Stress ${i}: ERROR"
	fi

	rm out 
done

