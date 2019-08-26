#!/bin/csh
#$ -N Ar               
#$ -pe mpi-8 8 
#$ -M tanggara@nd.edu
#$ -m abe
#$ -q long  

module load vasp/5.2.12-mpich2 
echo loading vasp

echo job was accepted on:
date

mpirun  -np $NSLOTS vasp > logfile

echo Vasp has completed.
date

echo --------------------------------------------------------
echo Logfile:
cat logfile
echo end logfile.
echo --------------------------------------------------------


exit 0

