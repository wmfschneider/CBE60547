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
1.6
1.7
1.8
1.9
2.0
2.1
2.2
2.3
2.4
2.5
2.6
2.7
2.8
2.9
3.0
EOF

cat <<'EOF' > template
 $BASIS GBASIS=STO NGAUSS=3 $END
 $CONTRL SCFTYP=RHF RUNTYP=ENERGY DFTTYP=SVWN ICHARG=0 MULT=1 $END
 $DATA 
Title
C1
He    2.0     0.   0.  0.
He    2.0     0.   0.  XXX
 $END
EOF

for i in  $(cat dist); do
    echo $i
    sed s/XXX/$i/ < template > $i.inp
    echo $i.inp
    rungms $i.inp > $i.out
    ENERGY=$(grep '^ FINAL R-SVWN' $i.out | gawk '{print $5}')
    echo "$i $ENERGY" >> summary.dat
done


