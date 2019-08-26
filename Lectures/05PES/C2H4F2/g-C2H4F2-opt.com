%chk=C2H4F2-opt1.chk
%mem=6MW
%nproc=1
#P HF/3-21G opt

C2H4F2 Scan

0   1
C
C   1   r1
F   2   r2   1   A1
H   2   r3   1   A2   3   D1   0
H   2   r3   1   A2   3   D2   0
F   1   r2   2   A1   3   D3   0
H   1   r3   2   A2   6   D1   0
H   1   r3   2   A2   6   D2   0

r1=1.5386
r2=1.39462
r3=1.11456
D1=120.47127
D2=-120.48305
A1=109.54214
D3=60.
A2=110.09239
