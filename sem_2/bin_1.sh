#!/bin/bash

if [ $# -eq 3 ]
then
    sum=$((($1+$2+$3)/3))
else
    echo "Incorrect count of args"
    exit 1
fi

echo "Result is: $sum"
