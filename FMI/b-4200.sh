#!/bin/bash

if [ ! -r $1 ] 
#|| [ "$1" != "*.c" ]
then
	echo "Invalid file"
	exit 1
fi

ans=$(sed 's/'"else {"'//g' $1 | grep '{' | wc -l)

echo "The deepest nesting is ${ans}"
