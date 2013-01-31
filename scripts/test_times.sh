#!/bin/bash

echo "portscan time testing"

for i in {1..20..2}
 do
  for j in {100..100..100}
   do
    echo "Using $i childs and $j ports"
    time portscan -d $1 -c $i -s 1 -e $j
  done
 done
