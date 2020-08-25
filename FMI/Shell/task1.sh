#!/bin/bash

if [ $# -ne 1 ]
then 
	echo "Invalid number of arguments"
	exit 1
fi

FILE=$1

if [[ ! -f ${FILE} ]]
then
	echo "File is unreadable"
	exit 2
fi

COUNT=$(cat ${FILE} | grep [2,4,6,8] | grep -v [a-w] | wc -l )

echo "${COUNT}"	
