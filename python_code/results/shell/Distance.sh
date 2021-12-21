#!/bin/bash
#################################################################
	#Taking the Distance's column from data 
       	#Author:Carlos Magno Ribeiro da Costa
	#e-mail:magno_costa@id.uff.br
        #How to run : type 'bash scriptCarlosMagnoRibeiroCosta.sh
	# nov/2021	
################################################################


for ang in $(seq 0 20 80)
do
	cat ../100k/results_ang$ang.txt | awk '{print $1}'>../100k/Distance_ang$ang.txt
	
	sed -i -e '1d' ../100k/Distance_ang*
done


