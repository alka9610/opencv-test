#!/bin/bash
cd imgs
for i in $( ls ); do
    echo imgs/$i
done
cd ..
