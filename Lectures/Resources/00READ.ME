

Input for FDA version 0.10 (12-Apr-95)
  by
David J. Heisterberg
Department of Chemistry
The Ohio State University

Line 1:
    int    np - number of grid points
    double x0 - coordinate of first grid point
    double xn - coordinate of last grid point

Line 2:
    int    niter - maximum number of iterations
    double cnv   - convergence criterion
    double mix1  - initial density mixing
    double mix2  - asymptotic density mixing
    double alpha - X-alpha alpha parameter
    double beta  - Becke's beta parameter (not used but required)

Line 3:
    double zn - nuclear charge
    int    no - number of orbitals

Line 4 (no times):
    int    n         - principal quantum number
    int    l         - angular quantum number
    double alpha occ - alpha occupation
    double beta occ  - beta occupation



Notes:

If alpha is < 0, |alpha| is used, but no potential "tail" correction
is performed.

Beta is a place-holder for now.  If gradient corrections are ever
implemented it should be set to 0.0042.

Alpha and beta occupations are checked but then added together as this
version isn't spin polarized.



General Description:

FDA is a knock-off of Herman and Skillman's 1963 code, sort of.

The Hamiltonian was supposed to be the same, yet fda gets
significantly different results, which, happily enough, are
much closer to those obtained with Froese Fischer's MCHF code.

FDA uses a different grid, with the spacing between grid points
growing by a constant factor.

FDA determines oribtals by finding eigenvectors of a tri-diagonal
operator matrix rather than using outward-inward integration.
Inverse iteration is used and sometimes eigenvectors will "collapse,"
especially for heavier atoms.  Should that happen, turn down the
mixing factors and turn up the iterations.

FDA requires no initial guess as to potential or eigenvalues.
Rather, it starts from a bare nucleus guess.

FDA calculates a total energy as well as a virial ratio (that
still isn't where it ought to be).

Finally, FDA is written in C++, with the aim of making the overall
structure of the calculation clear.



Building and Running:

FDA compiles reasonably cleanly with g++ and CRI's CC.  It should do
ok on most platforms, but you may need to change the .cxx extension
to .C (as on the Cray).

FDA will either read from stdin and write to stdout, or, if run as

    fda name

will read from name.inp, write to name.out, and generate an ASCII
dump file, name.dmp.  The contents of the dump file should be clear
from the source.  The dump file will eventually find use in generating
basis sets for a molecular code.  Eventually...



FDA is copyright 1995 by David J. Heisterberg.  Permission is hereby
granted to freely use FDA and redistribute it so long as this copy-
rigth notice is maintained and you don't laugh at the author.

Part of the reason for doing FDA was as an exercise in learning C++,
but the intention is to turn it into a real, usable code someday, so
please direct comments and scathing criticisms to

    djh@osc.edu    or
    heisterberg.1@osu.edu
