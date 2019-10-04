#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

cat <<EOF > dist
0.6
0.8
1.0
1.2
EOF

cat <<EOF > template
 $BASIS GBASIS=STO NGAUSS=3 $END
 $CONTRL SCFTYP=UHF RUNTYP=ENERGY ICHARG=1 $END
 $DATA 
Title
C1
H     1.0     0.   0.  0.
He    2.0     0.   0.  XXX
 $END
EOF

for i in  $(cat dist); do
    echo $i
    sed s/XXX/$i/ < template > $i.inp
    echo $i.inp
    rungms $1.inp > $1.out
    set ENERGY = grep '^ FINAL UHF' | gawk '{print $5}'
    echo "$i $ENERGY" >> summary.dat
done


