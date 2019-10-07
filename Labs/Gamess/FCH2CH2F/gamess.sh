#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

rungms opt.inp > opt.out


