#!/bin/bash


if [ $# -ne 2 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

A=$1
B=$2

mkdir a b c

for f in *
do
	if [ -f ${f} ]
	then 
		count=$( wc -l ${f} | awk '{print $1}' )
		echo "${count}"
		if [ ${count} -lt $1 ]
		then
			cp ${f} a
		elif [ ${count} -gt $1 ] && [ ${count} -lt $2 ]
		then
			cp ${f} b
		else
			cp ${f} c
		fi
	fi
done
