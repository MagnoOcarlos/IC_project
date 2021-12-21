#!/bin/bash
#################################################################
	#Using awk to make operations with file's column
       	#Author:Carlos Magno Ribeiro da Costa
	#e-mail:magno_costa@id.uff.br
        #How to run : type 'bash script-name.sh
	# nov/2021	
################################################################


for ang in $(seq 0 20 80)
do
	cat ../100k/results_ang$ang.txt | awk '{print $5}'>E.txt
	cat ../100k/results_ang$ang.txt | awk '{print $14}'>E0.txt
	
	sed -i -e '1d' E*

	paste E0.txt  E.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.3f\n", delta}' >../100k/delta_ang$ang.txt

	rm E*
done


