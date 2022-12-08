#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Incorrect count of args"
  exit 1
fi

tests=`find $2/test*`
it=0
for t in $tests
do
  it=$(($it+1))
  touch interm_$it.c
  cat $2/$1 $t > interm_$it.c
  gcc interm_$it.c -o interm_$it.out
  echo -e "\033[36mTest $it:\033[0m"
  ./interm_$it.out
  echo
done


rm *.out *.c

echo -e "\033[32mMission Complited\033[0m"
