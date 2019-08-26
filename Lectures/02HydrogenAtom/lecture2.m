%
% H atom orbitals and basis functions
% WFS August 30, 2007
%

clear all;
close all;

a0 = 1;  % work in units of bohr

V=@(r) -1/r;

h=figure('color',[1 1 1]);
set(h,'WindowStyle','Docked');
fplot(V,[0 10],'k:');
hold all;
xlabel('r (bohr)'); ylabel('Energy (hartree)')
axis([0 10 -2 1])

OneS=@(r) 2*exp(-r)-1/2;

TwoS=@(r) 2^-0.5*(1-r/2).*exp(-r/2)-1/4;

fplot(OneS,[0 10],'k-');
fplot(TwoS,[0 10],'r-')
legend('Coulomb','1s','2s')

plot([0 10],[-0.5 -0.5],'k--')
plot([0 10],[0 0],'k-')

plot([0 10],[-.25 -.25],'r--')


title('H Coulomb potential and 1s and 2s radial functions')

%
%  Gaussian functions
%
h=figure('color',[1 1 1]);
set(h,'WindowStyle','Docked');
fplot(V,[0 10])
hold all
syms S1 r
S1=2*exp(-r);
ezplot(S1,[0 10])

syms r gauss;
syms xi positive;
gauss=exp(-xi*r*r);
Norm2=int(r*gauss*r*gauss,r,0,inf);
Norm=1/sqrt(Norm2)
gauss=Norm*gauss;

% zeta = 1
gauss1=subs(gauss,xi,1)
E1 = int(r*gauss1*(-0.5*diff(diff(r*gauss1))-(1/r)*r*gauss1),0,inf)
eval(E1)

ezplot(gauss1,[0 10])

% zeta = 1 + zeta = 1/2
gauss12=gauss1+subs(gauss,xi,0.5);
Norm2=int(r*gauss12*r*gauss12,r,0,inf);
Norm=1/sqrt(Norm2)
gauss12=Norm*gauss12;
E2 = int(r*gauss12*(-0.5*diff(diff(r*gauss12))-(1/r)*r*gauss12),0,inf)
eval(E2)

ezplot(gauss12,[0 10])

% zeta = 1 + zeta = 1/2
gauss12p=gauss1+(3/2)*subs(gauss,xi,0.5);
Norm2=int(r*gauss12p*r*gauss12p,r,0,inf);
Norm=1/sqrt(Norm2)
gauss12p=Norm*gauss12p;
E3 = int(r*gauss12p*(-0.5*diff(diff(r*gauss12p))-(1/r)*r*gauss12p),0,inf)
eval(E3)

ezplot(gauss12p,[0 10])

axis([0 5 -1 3])
legend('Coulomb','1s','Gaussian(\zeta=1)','Gaussian(\zeta=1)+(\zeta=1/2)','Gaussian(\zeta=1)+1.5(\zeta=1/2)')
plot([0 10],[0 0],'k-')
title('Comparison of 1s and Gaussian functions')
