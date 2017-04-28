#!/bin/bash
for i in 4 8 16 24 28 32 40 48 64 80 96 112 128 256
do
	./pcritica.e $i
	echo $i 
done
