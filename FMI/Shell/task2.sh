#!/bin/bash

if [ $# -ne 1 ]
then 
	echo "Invalid number of argumnets"
	exit 1
fi

FILE=${1}

if [ ! -f ${FILE} ]
then 
	echo "Not a regular file"
	exit 2
fi

RES=$(cat ${FILE} | cut -d '-' -f2 | nl -s ". " | sort -k 2)
echo "${RES}" 

