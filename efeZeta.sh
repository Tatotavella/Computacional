#!/bin/bash
LANG=en_US
for i in $(seq 0 0.05 1)
do
	./efezeta.e 64 64 $i
	echo $i 
done
