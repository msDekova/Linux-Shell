#!/bin/bash
#Given three integers (X, Y, and Z) representing the three sides of a triangle, identify whether the triangle is Scalene, Isosceles, or Equilateral.

read X
read Y
read Z

if [ $X -ne $Y ] && [ $X -ne $Z ] && [ $Y -ne $Z ]
then
    echo SCALENE;
elif [ $X -eq $Y ] && [ $X -eq $Z ] && [ $Y -eq $Z ]
then 
    echo EQUILATERAL;
else
    echo ISOSCELES;
fi

