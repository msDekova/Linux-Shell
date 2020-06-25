#!/bin/bash

if [ $# -gt 3 ] || [ $# -lt 3 ]
then
	echo "Invalid number of arguments"
	exit 4
fi

N=$1
LEFT=$2
RIGHT=$3

#- 3, когато поне един от трите аргумента не е цяло число
#CHECK_INT=$(grep "^[0-9]+$")
ARGUMENTS="$1$2$3"
#echo "${ARGUMENTS}"
echo "${ARGUMENTS}" | grep -Eq "^[0-9]+$"
if [ $? -ne 0 ]
then 
	echo "Integers only"
	exit 3
fi

#- 2, когато границите на интервала са обърнати
if [ ${LEFT} -gt ${RIGHT} ]
then
	echo "Invalid interval"
	exit 2
fi

#- 1, когато числото не попада в интервала
#- 0, когато числото попада в интервала
if [ ${N} -lt ${LEFT} ] || [ ${N} -gt ${RIGHT} ]
then
	echo "The number is less than ${LEFT} or greater than ${RIGHT}"
        exit 1
else
	exit 0
fi
