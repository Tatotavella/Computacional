#!/bin/bash
for i in 4 16 32 64 128 256
do
	./curvapinf.e $i
	echo $i 
done
