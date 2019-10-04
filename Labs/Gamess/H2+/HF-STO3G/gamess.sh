#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

rm -f dist template summary.dat

cat <<EOF > dist
0.5
0.6
0.7
0.8
0.9
1.0
1.1
1.2
1.3
1.4
1.5
2.0
2.5
3.0
3.5
4.0
5.0
6.0
7.0
8.0
9.0
10.0
EOF

cat <<'EOF' > template
 $BASIS GBASIS=STO NGAUSS=3 $END
 $CONTRL SCFTYP=UHF RUNTYP=ENERGY ICHARG=1 MULT=2 $END
 $GUESS GUESS=HCORE $END
 $DATA 
Title
C1
H     1.0     0.   0.  0.
H     1.0     0.   0.  XXX
 $END
EOF

for i in  $(cat dist); do
    echo $i
    sed s/XXX/$i/ < template > $i.inp
    echo $i.inp
    rungms $i.inp > $i.out
    ENERGY=$(grep '^ FINAL UHF' $i.out | gawk '{print $5}')
    echo "$i $ENERGY" >> summary.dat
done


