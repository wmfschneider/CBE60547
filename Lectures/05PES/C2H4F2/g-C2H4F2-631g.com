%chk=C2H4F2-gdiis.chk
%mem=6MW
%nproc=1
#P HF/6-31G(d,p) opt=(cartesian,gdiis) geom=checkpoint

C2H4F2 Scan

0   1
