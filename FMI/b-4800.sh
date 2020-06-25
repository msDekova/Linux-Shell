#!/bin/bash

if [ $# -gt 2 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

FILE=$1
DIR=$2

if [ ! -f ${FILE} ] || [ ! -d ${DIR} ]
then
	echo "Invalid arguments"
	exit 1
fi

SEARCH=$(find ${DIR} -type f) 
#compare files with the same content

count=0
for i in ${SEARCH}
do
	cmp ${FILE} ${i}
	if [ $? -eq 0 ]
	then
		echo "${i}"
		((count++))
	fi
done

if [ ${count} -eq 0 ]
then
	exit 2
fi
