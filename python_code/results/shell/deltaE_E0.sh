#!/bin/bash
#################################################################
	#Using awk to make operations with file's columns, saving de Distance in a different file
        #and the arrival energy in another.
	#
	#To run this file look the bashs' scripts in geometry directory	
       	#Author:Carlos Magno Ribeiro da Costa
	#e-mail:magno_costa@id.uff.br
        #How to run : type 'bash script-name.sh
	# nov/2021	
################################################################


for ang in $(seq 0 20 80)
do
	cat $path/results_ang$ang.txt | awk '{print $5}'>E.txt
	cat $path/results_ang$ang.txt | awk '{print $14}'>E0.txt
	
	sed -i -e '1d' E*

	cp E.txt ang$ang

	paste E0.txt  E.txt | awk '{ delta=($1-$2)/($1) ; printf"%0.9f\n", delta}' >$path/delta_ang$ang.txt

	rm E*
	
	cat $path/results_ang$ang.txt | awk '{print $1}'>$path/Distance_ang$ang.txt
	
	sed -i -e '1d' ../100k/Distance_ang*
done


