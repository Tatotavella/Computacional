#!/bin/bash
LANG=en_US
tam=128
for i in $(seq 0 0.02 1)
do
	./nsNoperco.e $tam $i
	echo $i
done
