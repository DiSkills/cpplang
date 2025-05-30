#!/bin/bash

output=$(printf "2/3
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
1/2147483649")

res=$(./prog)
if [ x"$output" != x"$res" ]; then
    echo TEST FAILED "$res"
    exit 1
fi
