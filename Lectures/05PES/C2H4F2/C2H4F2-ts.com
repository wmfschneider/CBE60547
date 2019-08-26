%chk=C2H4F2-ts.chk
%mem=6MW
%nproc=1
#P HF/3-21G opt=(ts,calcfc)

C2H4F2 transition state search 

0   1
C
C   1   r1
F   2   r2   1   A1
H   2   r3   1   A2   3   D1   0
H   2   r4   1   A3   3   D2   0
F   1   r2   2   A1   3   D3   0
H   1   r3   2   A2   6   D1   0
H   1   r4   2   A3   6   D2   0

r1     1.52688
r2     1.40634
r3     1.07777
r4     1.07749
A1   109.51296
A2   112.00064
A3   108.18013
D1   119.60395
D2  -119.13814
D3   120.00000
