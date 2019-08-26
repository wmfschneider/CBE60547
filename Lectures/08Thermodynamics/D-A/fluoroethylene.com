%chk=c2h3f
%mem=6MW
%nproc=1
#N opt freq b3lyp/6-31g(d) 

fluoroethylene optimization

0 1
 C
 H                  1              B1
 H                  1              B2    2              A1
 C                  1              B3    3              A2    2              D1
 H                  4              B4    1              A3    3              D2
 F                  4              B5    1              A4    3              D3

   B1             1.07000000
   B2             1.07000000
   B3             1.35520000
   B4             1.07000000
   B5             1.35000000
   A1           119.88652694
   A2           119.88652694
   A3           120.22694612
   A4           119.88652694
   D1           180.00000000
   D2             0.00000000
   D3           180.00000000


