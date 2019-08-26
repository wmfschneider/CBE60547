%chk=ts-C2H4F2-PBE.chk
%mem=6MW
%nproc=1
#N B3LYP/6-31G(d) opt=(ts,calcfc,z-matrix)

C2H4F2 transition state search 

0   1
C
C   1   r1
F   2   r2   1   A1
H   2   r3   1   A2   3   D1   0
H   2   r4   1   A3   3   D2   0
F   1   r5   2   A4   3   D3   0
H   1   r6   2   A5   6   D4   0
H   1   r7   2   A6   6   D5   0

r1     1.52688
r2     1.40634
r5     1.41
r3     1.07777
r4     1.07749
r6     1.07749
r7     1.07749
A1   109.51296
A2   112.00064
A3   108.18013
A4   108.18013
A5   108.18013
A6   108.18013
D1   119.60395
D2  -119.13814
D3   120.00000
D4   119.0
D5  -120.0
