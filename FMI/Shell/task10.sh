#!/bin/bash

cat t10.txt | grep 'SI' | cut -d ':' -f 5 | cut -d ',' -f 1 > a.txt
cat t10.txt | grep 'SI' | cut -d ':' -f 6  > b.txt

paste -d ':' a.txt b.txt
