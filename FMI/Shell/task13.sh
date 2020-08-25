#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "The given argument is not a directory"
	exit 2
fi

find ${1} -type l ! -exec test -e {} \; -print
