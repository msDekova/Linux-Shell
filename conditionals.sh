#!/bin/bash
#Read in one character from the user (this may be 'Y', 'y', 'N', 'n'). If the character is 'Y' or 'y' display "YES". If the character is 'N' or 'n' display "NO". No other character will be provided as input.

read character
case $character in
    [Yy]) echo "YES";;
    [Nn]) echo "NO";;
esac


