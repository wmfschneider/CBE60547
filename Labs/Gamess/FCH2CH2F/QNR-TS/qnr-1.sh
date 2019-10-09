#!/bin/bash
#$ -pe smp 4
#$ -q debug
#$ -N gamess
module load gamess

THISNAME=qnr-1
MYRUNGAMESS=$HOME/CBE60547/Labs/Gamess/bin/rungms

cat <<EOF > ~/.gmsrc
set SCR=/scratch365/$USER
set USERSCR=$PWD
EOF

cat<<'EOF' > $THISNAME.inp
 $CONTRL SCFTYP=RHF DFTTYP=PBE RUNTYP=OPTIMIZE COORD=ZMT NZVAR=18 ISPHER=1 $END
 $STATPT METHOD=NR $END
 $BASIS GBASIS=PCseg-1 $END
 $DATA
FCH2CH2F zmatrix optimization near saddle point, no hessian
C1
 C   
 C      1   1.5256029
 F      2   1.4018052  1   110.3919125
 H      2   1.1066523  1   112.5759655  3   119.5903058  0
 H      2   1.1070172  1   108.5521191  3  -119.1579857  0
 F      1   1.4018888  2   110.3079213  3   120.0000000  0
 H      1   1.1065092  2   112.5372024  6   119.5247291  0
 H      1   1.1069911  2   108.5976341  6  -119.1645584  0
 $END

EOF
$MYRUNGAMESS $THISNAME.inp > $THISNAME.out

grep 'NSERCH:' $THISNAME.out | gawk '{print $4, $7, $9}' > $THISNAME.sum

