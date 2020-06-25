#!/bin/bash

if [ $# -lt 1 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

N=$1

if [ $# -eq 1 ]
then
	DELIMITER=" "
else
	DELIMITER=$2
fi

echo "${N}" | rev | sed "s/[0-9]\{3\}/&$DELIMITER/g" | rev
