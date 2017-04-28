#!/bin/bash
LANG=en_US
for i in $(seq 0 0.02 1)
do
	./gammamatch.e 128 128 $i
	echo $i 
done
