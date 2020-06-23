#!/bin/bash

echo "username:" 
read USR

echo "The user ${USR} has $(who | grep ${USR} | wc -l) active sessions"
