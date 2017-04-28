#!/bin/bash
tams=(4 16 32 64 128)
probas=(0.56286 0.58775 0.59409 0.59263 0.59255)

for index in ${!tams[*]}
do
	./nsfrag.e ${tams[$index]} ${probas[$index]}
done
