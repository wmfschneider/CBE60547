#!/bin/csh
#$ -N CompChemistry
#$ -M wschneider@nd.edu
#$ -m abe
#$ -pe smp 4
#$ -q short

module load vasp/4.6


echo job was accepted on:
date
hostname
pwd
ls -l

mpirun -np $NSLOTS vasp > log
#vasp > log

echo Vasp has completed.
date

exit 0
