%chk=CH3OH-631g.chk
%mem=6MW
%nproc=1
#P HF/6-31G(d) opt

CH3OH optimization

0   1
C
O   1   r1
H   2   r2   1   A1
H   1   r3   2   A2   3   D1   0
H   1   r4   2   A3   3   D2   0
H   1   r4   2   A3   3  -D2   0

r1=1.4
r2=1.1
r3=1.1
r4=1.1
A1=120.
A2=109.54214
A3=109.54214
D1=180.0
D2=120.48305
