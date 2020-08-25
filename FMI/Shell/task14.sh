#!/bin/bash

if [ $# -ne 1 ]
then 
	echo "Invalid number of argumnets"
	exit 1
fi

USER=$(whoami)
if [[ "${USER}" != root ]]
then
	echo "The script is not run by root"
	exit 2
fi

USERS=$(mktemp)
ps -e -o user | sort | uniq | sed 1d > "${USERS}"

cat "${USERS}"

while read CURR_USER
do
	TOTAL_RSS=0
	while read PID RSS
	do
		TOTATAL_RSS=$(expr ${TOTAL_RSS} + ${RSS})
		LAST_PID="${PID}"
	done < <(ps -u "${CURR_USER}" -o pid,rss | sort -k2)

	if [ "${TOTAL_RSS}" -gt ${1} ]
	then
		kill -s TERM "${LAST_PID}"
		sleep 1
		kill -s KILL "${LAST_PID}"
	fi

done < "${USERS}" 

rm -- "${USERS}"
