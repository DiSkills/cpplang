#!/bin/bash

output=$(printf "2/3
39/45
162/135
-6/45
-135/135
2/1
5/2 2.500000 2 3
1/2
4/6
24/24")

res=$(./prog)
if [ x"$output" != x"$res" ]; then
    echo TEST FAILED "$res"
    exit 1
fi
