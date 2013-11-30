#!/bin/sh

FILES="b14 c01 mc11 brasil58 cc3-4p i160-003 i160-033 d10 hc10p e20"

make clean
make -B

for file in $FILES; do
	for i in 1 2 3 4 5 6 7 8 9 10; do
		echo "Execution " $i " - " file=$file.stp >> out_$file.txt
		./steinertree < ../instancias/$file.stp >> out_$file.txt
	done
done




