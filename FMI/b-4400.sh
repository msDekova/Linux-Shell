#!/bin/bash

if [ $# -gt 2 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

dir_to_copy=$1

if [ ! -d "$2" ]
then
	dest_dir=$(date '+%Y-%m-%d')
	mkdir "${dest_dir}"
else
	dest_dir="$2"
fi


cp $(find "${dir_to_copy}" -mmin -45 -type f) "${dest_dir}"
