#!/bin/bash

if [ $# -ne 3 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

#$(paste $1 $2 | sort -s ) >> $3
paste $1 $2 | sort > $3 

cat $3
