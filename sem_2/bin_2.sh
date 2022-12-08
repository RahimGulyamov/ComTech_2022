#!/bin/bash
if [ $# -eq 2 -a -f"$1" -a -f"$2" ]
then
  sum=$1$2
  touch $sum
  cat $1 $2 > $sum
else
  echo "Incorrect data"
  exit 1
fi
