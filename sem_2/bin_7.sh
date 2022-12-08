#!/bin/bash

if [ $# -ne 2 ]
then
  echo "Incorrect count of args"
  exit 1
fi

if [ ! -d "$1" -a ! -d "$2" ]
then
  echo "Args are not DIR"
  exit 1
fi

find $1/ $2/ -type f -print0 | awk -F/ 'BEGIN { RS="\0" } { n=$NF } k[n]==1 { print p[n]; } k[n] { print $0 } { p[n]=$0; k[n]++ }' > same_names.sh
ls -t `cat same_names.sh` > same_names_2.sh
sm_fls=`cat same_names_2.sh`
rm same_names*

echo $sm_fls

if [ ! "$sm_fls" ]
then
 echo "No files with same names"
  exit 1
fi

if [ ! -d BKP ]
then
  mkdir BKP
  echo "DIR BKP/ was created"
fi

i=0

declare -a fl_arr


for fl in $sm_fls
do
  n=0
  bool=0

  while [ ${fl:$n:1} != "/" ]
  do
    n=$(($n+1))
  done
  n=$(($n+1))


  a=0

  for (( a=0; a < $i; a++ ))
  do
    if [ ${fl_arr[$a]} = ${fl:$n} ]
    then
      bool=1
    fi
  done
  if [ $bool -eq 1 ]
  then
    echo "Continued"
    fl_arr[i]=${fl:$n}
    i=$(($i+1))
    continue
  fi
  fl_arr[i]=${fl:$n}
  echo ${fl_arr[i]} $i


  empt=`cat $fl`

  if [ ! "$empt" ]
  then
    echo "File $fl is EMPTY"
    fl_arr[i]=${fl:$n}
    i=$(($i+1))
    continue
  fi
  if [ "$fl" = "$1/${fl_arr[i]}" ]
  then
    date=`date`
    len=${#date}
    cat "$2/${fl_arr[i]}" > BKP/${fl_arr[i]}.bkp."${date:0:$len-4}"
    cp $fl $2
    echo "$2  BKP"
  else
    date=`date`
    len=${#date}
    echo "fl_arr   "  ${fl_arr[i]}
    cat "$1/${fl_arr[i]}" > BKP/${fl_arr[i]}.bkp."${date:0:$len-4}"
    cp $fl $1
    echo "$1 BKP"
  fi
  echo "FINISH"
  i=$(($i+1))
done


