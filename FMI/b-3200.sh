#!/bin/bash

read -p "Enter a directory: " DIR

echo "Number of files and subdirectories in ${DIR} directory is $(find ${DIR} | wc -l)"
echo "Number of files in ${DIR} is $(find ${DIR} -type f | wc -l)"
echo "Number of subdirectories in ${DIR} is $(find ${DIR} -type d | wc -l)"
