#!/bin/bash
#Given N integers, compute their average correct to three decimal places.

read n

i=0
sum=0

while [ $i -lt $n ]
do
    read num
    sum=$((sum + num))
    i=$((i+1))
done

#avg=$((sum/n))
printf "%.3f" $(echo $sum/$n | bc -l)
