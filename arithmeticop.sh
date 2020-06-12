#!/bin/bash
#We provide you with expressions containing +,-,*,^, / and parenthesis. None of the numbers in the expression involved will exceed 999. 
#Your task is to evaluate the expression and display the correct output rounding upto 3 decimal places.

read input
# bc - An arbitrary precision calculator language
# -l -  Define the standard math library.
echo $input | bc -l | xargs printf "%.3f"
