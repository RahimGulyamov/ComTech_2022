#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Incorrect count of args"
  exit 1
fi

tests=`find $2/test*`
ans=`cat $2/$1`


c_ans=0
c_tests=0

for i in $tests
do
  c_tests=$(($c_tests+2))
done

for i in $ans
do
  c_ans=$(($c_ans+1))
done


if [ $c_tests -ne $c_ans ]
then
  echo "Counts of tests and answers are not equal"
  exit 1
fi

c_tests=0

declare -a tt

for t in $tests
do
  touch interm.c
  cat $2/func_4.c $t > interm.c
  gcc interm.c -o interm.out
  tt[$c_tests]=`./interm.out`
  c_tests=$(($c_tests+1))
  rm interm.*
done

c_tests=0
c_ans=0


for i in $ans
do
  c_ans=$(($c_ans+1))
  c_tests=$(($c_ans/2-1))
  if [ $(($c_ans%2)) -ne 1 ]
  then
    aa="$aa $i "
    tt2="${tt[$c_tests]}"

    if [ "$aa" = "$tt2" ]
    then
      echo -e "\033[32mTEST $(($c_tests+1)) PASSED\033[0m"
    else
      echo -e "\033[31mTEST $(($c_tests+1)) FAILED\033[0m"
      echo "Expected : $aa"
      echo "Result is : $tt2"
    fi
  fi
  aa=$i
done
