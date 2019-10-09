#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

THISNAME=zmat-1
MYRUNGAMESS=$HOME/CBE60547/Labs/Gamess/bin/rungms

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

cat<<'EOF' > $THISNAME.inp
 $CONTRL SCFTYP=RHF DFTTYP=PBE RUNTYP=OPTIMIZE COORD=ZMT NZVAR=18 ISPHER=1 $END
 $BASIS GBASIS=PCseg-1 $END
 $DATA
FCH2CH2F cartesian optimization calculation
C1
 C   
 C      1   1.5231820
 F      2   1.4425887  1   108.9141055
 H      2   1.1093304  1   110.6816081  3   119.6722433  0
 H      2   1.1071023  1   109.4687372  3  -118.8753319  0
 F      1   1.4425956  2   108.9160521  3    73.3324915  0
 H      1   1.1093293  2   110.6833783  6   119.6739766  0
 H      1   1.1071084  2   109.4682599  6  -118.8746540  0
 $END

EOF
$MYRUNGAMESS $THISNAME.inp > $THISNAME.out

grep 'NSERCH:' $THISNAME.out | gawk '{print $4, $7, $9}' > $THISNAME.sum

