#!/bin/bash

if [ $# -gt 1 ]
then
	echo "Invalid number of arguments"
	exit 1
fi

ID=$1

until (who | grep "${ID}")
do
	echo "Sleeping"
	sleep 1
done
