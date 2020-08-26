#!/bin/bash

if [ $# -ne 3 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

if [ ! -f ${1} ]
then
	echo "First argument must be regular file"
	exit 2
fi


FILE=$1
STRING1=$2
STRING2=$3

TERM1=$(cat ${FILE} | grep "${STRING1}=" | cut -d '=' -f2 | tr ' ' '\n' | sort | uniq | sed 1d )
TERM2=$(cat ${FILE} | grep "${STRING2}=" | cut -d '=' -f2 | tr ' ' '\n' | sort | uniq )
echo "${TERM1}"
echo "${TERM2}"

RES=$(echo "${TERM2}" | grep -v "${TERM1}" | tr '\n' ' ')
_TERM1=$(echo "${TERM1}" | tr '\n' ' ' )
_TERM2=$(echo "${TERM2}" | tr '\n' ' ' )

#echo "${RES}"
sed -i -e "s/^${STRING2}=.*/${STRING2}=${RES}/" "${FILE}"
