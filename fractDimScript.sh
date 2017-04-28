#!/bin/bash
tams=(4 16 32 64 128 256)
probas=(0.561110 0.588126 0.593725 0.592220 0.592586 0.592749)

for index in ${!tams[*]}
do
	./fractDim.e ${tams[$index]} ${probas[$index]}
done
