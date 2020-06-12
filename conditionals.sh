#!/bin/bash
#Read in one character from the user (this may be 'Y', 'y', 'N', 'n'). If the character is 'Y' or 'y' display "YES". If the character is 'N' or 'n' display "NO". No other character will be provided as input.

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

