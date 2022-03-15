#!/bin/bash

home=/home/magnum/Desktop/IC/python_code/geometry
run=/home/magnum/Desktop/IC/python_code/results/shell
plot=/home/magnum/Desktop/IC/python_code/results/100k/plots

#Angle's loop
for((j=0;j<=80;j=j+20))
do
#loop from radius 20 Mpc to 80 Mpc
	for((i=20; i<=80; i=i+20)) 
	do
		#Create a directory to each different radius 
		mkdir -p ../results/one_sphere/ang_${j}
	
		cp *radius_${i}_Mpc_one_* aux.txt
		
		#removing the header of crpropa's file 
		sed -i "1s/#//g" aux.txt 
		sed -i '/^#/d' aux.txt

		
		python  geometry.py aux.txt $j ../results/one_sphere/ang_${j}/results_R$i.txt
	
 
	done

	cd ../results/one_sphere/ang_${j}
	
	mkdir -p plot/pdfs_saved

	dir=$(echo $PWD)
	#adding the path to the script run.sh , which make all the operations 
	#to create the files needed to the plot 

	sed -i "12 a path=$dir" $run/Fixed_angle_run.sh

	bash $run/Fixed_angle_run.sh
	cd plot/
	cp $plot/Fixed_angle_*.cc .
	
#	sed -i "47s/103/$(($i+100))/g" Fixed_angle_distance_hist.cc
#	sed -i "47s/3/$i/g" Fixed_angle_distance_hist.cc 

	sed -i "175s/Energy_spectrum.pdf/Energy_spectrum_angle$j.pdf/g" Fixed_angle_energy_spectrum.cc
	sed -i "175s/Distance.pdf/Distance_angle$j.pdf/g" Fixed_angle_distance_hist.cc
	sed -i "175s/DeltaE_E0.pdf/DeltaE_E0_angle$j.pdf/g" Fixed_angle_deltaE_E0.cc
	
	#making the plots
	g++ Fixed_angle_deltaE_E0.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe
	
	g++ Fixed_angle_distance_hist.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe

	g++ Fixed_angle_energy_spectrum.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe
	
	#deleting all unnecessaries files
	rm plot.exe
	rm ../*.txt
        rm *.cc

	sed -i "/^path=/d" $run/Fixed_angle_run.sh
	cd $home
	rm aux.txt
done
