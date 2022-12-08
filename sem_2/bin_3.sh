#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Incorrect count of args"
  exit 1
fi

if [ ! -d "$1" ]
then
  echo "Directory was created"
  mkdir $1
fi

if [ ! -f "$2" ]
then
  echo "File doesn't exist"
  exit 1
fi

list_1=`ls -l -d $1`
list_2=`ls -l $2`
it=0

for own1 in $list_1
do
  it=$(($it+1))
  if [ $it -eq 3 ]
  then
    it=0
    for own2 in $list_2
    do
      it=$(($it+1))
      if [ $it -eq 3 ]
      then
        if [ $own1 = $own2 ]
        then
          cp $2 $1
          echo "File was copied"
        else
          echo "Owners don't coincide"
          exit 1
        fi
      fi
    done
  fi
done
