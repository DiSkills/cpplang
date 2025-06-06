#!/bin/bash

TARGET=prog

g++ -ggdb -Wall -o$TARGET rational.cpp

EXPECTED=$(printf "2/3
1/5
13/15
7/15
-2/15
-1/1
2/1
5/2 2.500000 2 3
1/2
2/3
1/1
0/1
1/1
0/1
1/1
-2/1
2/1
2/1
-2/1
1/2147483649
The denominator turned out to be zero")

res=$(./$TARGET)
rm $TARGET
if [ x"$EXPECTED" != x"$res" ]; then
    echo TEST FAILED
    echo "$res"
    exit 1
fi
