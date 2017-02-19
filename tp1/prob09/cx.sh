#!/bin/bash
SRCFILE="$1.c"
BINFILE+="$1.o"

# Remove previously compiled files
rm -f $BINFILE
rm -f $1

# Compile program   
cc -o $1 $SRCFILE

# Check compilation's result
if [ $? -ne 0 ]
then
    echo "Compilation Error!"
else
    echo "Compiled!"
    ./p7aa
fi

