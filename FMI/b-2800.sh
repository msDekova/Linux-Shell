#!/bin/bash

read N

command=$(echo ${N} | grep -e [^[:alnum:]] --color | wc -l)  

if [ ${command} -eq 0 ]
then 
	exit 0
else
	exit 1
fi
