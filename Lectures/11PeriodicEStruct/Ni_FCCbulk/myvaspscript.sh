#!/bin/csh
#$ -M dmccalma@nd.edu
#$ -m abe
#$ -pe hmf* 4
module load pathscale
echo loading pathscale
module load mpich/x86_64/1.2.7-ch_p4-path
echo loading mpich
mpirun -np $NSLOTS -machinefile $TMPDIR/machines /opt/und/vasp/x86_64/vasp.4.6/vasp


