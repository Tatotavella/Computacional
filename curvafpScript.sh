#!/bin/bash
for i in 4 16 32 64 128 256
do
	./curvafp.e $i
	echo $i 
done
