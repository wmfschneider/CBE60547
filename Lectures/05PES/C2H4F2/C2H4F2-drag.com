%chk=C2H4F2-drag.chk
%mem=6MW
%nproc=1
#N HF/3-21G opt=z-matrix NOSYMMETRY

C2H4F2 Coordinate Drag

0   1
C
C   1   r1
F   2   r2   1   A1
H   2   r3   1   A2   3   D1   0
H   2   r4   1   A3   3   D2   0
F   1   r2   2   A1   3   D3   0
H   1   r3   2   A2   6   D1   0
H   1   r4   2   A3   6   D2   0

r1=1.5386
r2=1.39462
r3=1.11456
r4=1.12
A1=109.54214
A2=111.
A3=110.
D1=120.
D2=-120.5
D3=50. S  26   5.
