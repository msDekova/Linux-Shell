#!/bin/bash

if [ $# -lt 4 ] || [ $# -gt 4 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

FILE=$1
NAME="$2 $3"
NICKNAME=$4

USER_ID=$(grep -w '${NAME}' /etc/passwd | cut -d ":" -f 1)
echo "${NICKNAME} ${USER_ID}" >> ${FILE}
