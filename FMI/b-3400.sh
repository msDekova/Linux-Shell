#!/bin/bash

read -p "Input file name: " FILE
read -p "Input string: " STR

if [ ! -r ${FILE} ]
then
	echo "Invalid file"
	exit 1
fi

ans=$(grep -F "${STR}" "${FILE}" | wc -l) 

if [ ${ans} -lt 1 ]
then
	exit 1
else
	exit 0
fi

echo "$?"
