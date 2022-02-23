#!/bin/bash

home=/home/magnum/Desktop/IC/python_code/geometry
run=/home/magnum/Desktop/IC/python_code/results/shell
plot=/home/magnum/Desktop/IC/python_code/results/100k/plots

#loop from radius 20 Mpc to 80 Mpc
for((i=20; i<=80; i=i+20)) 
do
	#Create a directory to each different radius 
	mkdir -p ../results/one_sphere/${i}_Mpc
	
	#loop for the angles and to run the geometry code to each one
	for((j=0; j<=80; j=j+20))
	do
		cp *radius_${i}_Mpc_one_* aux.txt

		sed -i "1s/#//g" aux.txt 
		sed -i '/^#/d' aux.txt


		python  geometry.py aux.txt $j ../results/one_sphere/${i}_Mpc/results_ang$j.txt
	done
	
	cd ../results/one_sphere/${i}_Mpc
	
	mkdir -p plot/pdfs_saved

	dir=$(echo $PWD)

	sed -i "12 a path=$dir" $run/run.sh

	bash $run/run.sh
	cd plot/
	cp $plot/*.cc .

	g++ DeltaE_E0.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe
	
	g++ Distance_hist.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe

	g++ Energy_spectrum.cc -o plot.exe `root-config --cflags --glibs`
	./plot.exe

	rm plot.exe
	rm ../*.txt
	rm *.cc

	sed -i "/^path=/d" $run/run.sh
	cd $home
	rm aux.txt 
done
