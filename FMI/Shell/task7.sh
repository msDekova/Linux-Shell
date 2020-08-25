#!/bin/bash

echo "$( cat passwd_file | cut -d ':' -f 1,5 | cut -d ',' -f 1 | grep --color '[a]$' | cut -b 3,4 | uniq -c | sort -k 1 | tail -n 1 )"
