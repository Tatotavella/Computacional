#!/bin/bash
LANG=en_US
for i in $(seq 0.58 0.001 0.6)
do
	./gammamatch.e 128 128 $i
	echo $i 
done
