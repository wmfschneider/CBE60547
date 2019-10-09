#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

THISNAME=opt-cart

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

cat<<'EOF' > $THISNAME.inp
 $CONTRL SCFTYP=RHF DFTTYP=PBE RUNTYP=OPTIMIZE COORD=CART ISPHER=1 $END
 $BASIS GBASIS=PCseg-0 $END
 $DATA
FCH2CH2F cartesian optimization calculation
C1
N 7 0.00000000 0.00000000 0.00000000
N 7 0.87068800 0.43708500 0.02898800
O 8 1.32984400 -0.10682200 -0.01102700
H 1 -0.01026300 -0.60188200 0.19954500
H 1 -0.37370800 0.29781100 -0.17504000
 $END

EOF
~/bin/rungms $THISNAME.inp > $THISNAME.out

grep 'NSERCH:' $THISNAME.out | gawk '{print $4, $7, $9}' > $THISNAME.sum

