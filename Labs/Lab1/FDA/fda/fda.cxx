#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#include "basis.h"
#include "vector.h"
#include "overlap.h"
#include "del2.h"
#include "rp1.h"
#include "rm1.h"
#include "rm2.h"
#include "jandx.h"
#include "hamilx.h"
#include "densityx.h"
#include "orbital.h"
#include "nl.h"

#define MAX(x, y) ((y) > (x) ? (y) : (x))

static char llabels [] = "spdfgh";
#define MAXMAXL 5

/*
* fda
* a finite difference atomic structure program
* based on Hermann-Skilman
*/
int main (int argc, char * argv []) {

/*
* files
*   inp - input file
*   out - output file
*   dmp - binary dump file
*/
  static char inp_ext [] = ".inp";
  static char out_ext [] = ".out";
  static char dmp_ext [] = ".dmp";

  char * job_name, * inp_name, * out_name, * dmp_name;
  FILE * inp = stdin;
  FILE * out = stdout;
  FILE * dmp;

  int np;
  double x0, xn;
  int maxitr;
  double conver, mix, mix1, mix2, alpha, beta;
  double zn;
  int no, nmax, lmax;
  double za, zb, ze;

/*
* miscellaneous, indices, etc.
*/
  double cnv, den;
  double kin, pot, onee, twoe, en;
  int i, ix, j, k, l, m, n, itr;

/*
* ready to go
* check the command line
*/
  if (argc == 1) {
    job_name = 0;
    }
  else if (argc == 2) {
    job_name = argv [1];
    inp_name = new char [strlen (job_name) + strlen (inp_ext) + 1];
    out_name = new char [strlen (job_name) + strlen (out_ext) + 1];
    dmp_name = new char [strlen (job_name) + strlen (dmp_ext) + 1];
    }
  else {
    printf ("Usage: %s [job-name]\n", argv [0]);
    exit (-1);
    }

/*
* open files
*/
  if (job_name == 0) {
    inp = stdin;
    }
  else {
    strcpy (inp_name, job_name);
    strcat (inp_name, inp_ext);
    if ((inp = fopen (inp_name, "r")) == 0) {
      fprintf (stderr, "%s: Cannot open input file %s\n", argv [0], inp_name);
      exit (-1);
      }
    }

  if (job_name == 0) {
    out = stdout;
    }
  else {
    strcpy (out_name, job_name);
    strcat (out_name, out_ext);
    if ((out = fopen (out_name, "w")) == 0) {
      fprintf (stderr, "%s: Cannot open output file %s\n", argv [0], out_name);
      exit (-1);
      }
    }

  if (job_name == 0) {
    if ((dmp = fopen ("/dev/null", "w")) == 0) {
      fprintf (stderr, "%s: Cannot open /dev/null\n", argv [0]);
      exit (-1);
      }
    }
  else {
    strcpy (dmp_name, job_name);
    strcat (dmp_name, dmp_ext);
    if ((dmp = fopen (dmp_name, "w")) == 0) {
      fprintf (stderr, "%s: Cannot open dump file %s\n", argv [0], dmp_name);
      exit (-1);
      }
    }

/*
* read initial input to get sizes
*/
  fscanf (inp, "%d %le %le\n", &np, &x0, &xn);
  fscanf (inp, "%d %le %le %le %le %le\n",
          &maxitr, &conver, &mix1, &mix2, &alpha, &beta);
  fscanf (inp, "%le %d\n", &zn, &no);
  mix1 = (mix2 - mix1) / mix1;

/*
* create the operators and such
*/
  basis_c   rr (np, zn, x0, xn);

  overlap_c  ss (&rr);
  del2_c     ke (&rr);
  rp1_c      xr (&rr);
  rm1_c      vn (&rr);
  rm2_c      va (&rr);
  densityx_c da0 (&rr);
  densityx_c da1 (&rr);
  jandx_c    jk (&rr);
  hamilx_c   ha (&rr);

  vector_c dd (&rr);
  vector_c un (&rr);
  un ^= 1.0;

  orbital_c *pp = new orbital_c [no];
  if (pp == 0) {
    fprintf (stderr, "fda: cannot allocate orbitals\n");
    exit (errno);
    }
  for (i = 0; i < no; i++) {
    pp [i].orbital (&rr);
    }

/*
* read the orbital information
*/
  nmax = 0;
  lmax = 0;
  za = zb = 0.0;
  for (i = 0; i < no; i++) {
    fscanf (inp, "%d %d %le %le\n",
            &pp [i].n, &pp [i].l, &pp [i].occ [0], &pp [i].occ [1]);

    if (pp [i].n < 1) {
      fprintf (stderr, "orbital %d: bad principal quantum number\n", i+1);
      exit (-1);
      }
    if (pp [i].n > nmax) nmax = pp [i].n;

    if ((pp [i].l < 0) || (pp [i].l >= pp [i].n) || (pp [i].l >= MAXMAXL)) {
      fprintf (stderr, "orbital %d: bad angular quantum number\n", i+1);
      exit (-1);
      }
    if (pp [i].l > lmax) lmax = pp [i].l;

    if ((pp [i].occ [0] < 0.0) || (pp [i].occ [0] > 2 * pp [i].l + 1)) {
      fprintf (stderr, "orbital %d: bad alpha occupation\n", i+1);
      exit (-1);
      }
    if ((pp [i].occ [1] < 0.0) || (pp [i].occ [1] > 2 * pp [i].l + 1)) {
      fprintf (stderr, "orbital %d: bad beta occupation\n", i+1);
      exit (-1);
      }

    za += pp [i].occ [0];
    zb += pp [i].occ [1];
    }

  ze = za + zb;
  fprintf (out, "zn = %10.5f, ze = %10.5f\n", zn, ze);

/*
* build the orbital index
* n = l entry used to denote maximum n for l
*/
  nl_c nl (nmax);
  for (i = 0; i <= nmax; i++) {
    for (j = 0; j <= i; j++) {
      nl (i, j) = -1;
      }
    }

  for (i = 0; i < no; i++) {
    nl (pp [i].n, pp [i].l) = i;
    if (pp [i].n > nl (pp [i].l, pp [i].l)) nl (pp [i].l, pp [i].l) = pp [i].n;
    }
  
/*
* initialize densities and coulomb-exchange
*/
  da0 ^= 0.0;
  dd ^= 0.0;
  jk ^= 0.0;

/*
* initialize orbitals based on core guess
*/
  for (i = 0; i < no; i++) {
    pp [i].e = -(zn * zn) / (2 * pp [i].n * pp [i].n);
    pp [i].guess ();
    cnv = 1.0 / sqrt (ss.gdot (pp [i], pp [i]));
    pp [i] *= cnv;
    }

/*
* do maxitr times or until convergence
*/
  for (itr = 0; itr < maxitr; itr++) {
    fprintf (out, "itr = %d\n", itr);

/*
* do for each angular momentum
*/
    for (l = 0; l <= lmax; l++) {
      if (nl (l, l) <= 0) continue;
      fprintf (out, "  l = %d\n", l);

/*
* generate the hamiltonian
*/
      ha.hamilx (ke, zn, vn, l, va, jk);

/*
* do iterative update to get new eigenvectors
*/
      for (i = l+1; i <= nl (l, l); i++) {
        ix = nl (i, l);
        if (ix < 0) continue;
        pp [ix].e = ha.geigen (conver, pp [ix].e, ss, pp [ix]);
        fprintf (out, "    n = %d, e = %16.8f (%16.8f)\n",
                 pp [ix].n, pp [ix].e, 2*pp [ix].e);
        }
 
      } /* for l */

/*
* generate new density matrices and density change
*/
    da1.densityx (no, 0, pp);
    for (i = 0; i < np; i++) {
      dd (i) = fabs (da0 (i, i) - da1 (i, i));
      }

/*
* find convergence
*/
    cnv = ss.gdot (un, dd) / MAX (ze, 1.0);
    mix = mix2 / (mix1 * cnv + 1.0);
    fprintf (out, "  cnv = %10.6f, mix = %10.6f\n", cnv, mix);

/*
* mix old and new densities
*/
    da0 *= (1.0 - mix);
    da1 *= mix;
    da0 += da1;

/*
* generate new diagonal density and check how much is accounted for
*/
    for (i = 0; i < np; i++) {
      dd (i) = da0 (i, i);
      }
    den = ss.gdot (un, dd);
    fprintf (out, "  integrated charge = %10.6f out of %10.6f\n", den, ze);
    fflush (out);
    if (den > ze) {
      da0 *= ze / den;
      }

/*
* generate new jk
*/
  jk.jandx (alpha, beta, ze, da0);

/*
* exit if converged
*/
    if (cnv < conver) break;
    }

/*
* print final one-electron values
*/
  double rad;
  fprintf (out, "\n                   Orbital Summary\n");
  fprintf (out, " nl    occ        E           KE       <1/r>     <r>\n");
  for (ix = 0; ix < no; ix++) {
    den = pp [ix].occ [0] + pp [ix].occ [1];
    l = pp [ix].l;
    kin = -0.5 * ke.gdot (pp [ix], pp [ix]) +
           l*(l+1)/2 * va.gdot (pp [ix], pp [ix]);
    pot = vn.gdot (pp [ix], pp [ix]);
    rad = xr.gdot (pp [ix], pp [ix]);
    fprintf (out, " %1d%1c %6.2f %12.4f %11.4f %9.4f %8.4f\n",
             pp [ix].n, llabels [l], den, pp [ix].e, kin, pot, rad);
    }

/*
* do total energy and virial
*/
  kin = pot = onee = twoe = 0.0;
  for (i = 0; i < no; i++) {
    den = pp [i].occ [0] + pp [i].occ [1];
    l = pp [i].l * (pp [i].l + 1) / 2;

    en = den * -0.5 * ke.gdot (pp [i], pp [i]);
    kin += en;
    onee += en;

    en = den * (-zn * vn.gdot (pp [i], pp [i]));
    pot += en;
    onee += en;

    en = den * (l*va.gdot (pp [i], pp [i]));
    kin += en;
    onee += en;

    en = den * 0.5 * jk.gdot (pp [i], pp [i]);
    pot += en;
    twoe += en;
    }

  fprintf (out, "\n     Energy Summary\n");
  fprintf (out, " kinetic energy      = %10.4f\n", kin);
  fprintf (out, " potential energy    = %10.4f\n", pot);
  fprintf (out, " one-electron energy = %10.4f\n", onee);
  fprintf (out, " two-electron energy = %10.4f\n", twoe);
  fprintf (out, "\n");
  fprintf (out, " total energy = %10.4f\n", kin + pot);
  fprintf (out, " virial ratio = %10.4f\n", pot / kin);

/*
* make all orbitals start out positive
*/
  for (j = 0; j < no; j++) {
    if (pp [j] (0) < 0.0) pp [j] *= -1.0;
    }

/*
* dump the results
*/
  fprintf (dmp, "fda 00.10\n");
  fprintf (dmp, "%8d %15.8e %15.8e\n", np, x0, xn);
  fprintf (dmp, "%15.8e %7d\n", zn, no);
  for (i = 0; i < np; i++) {
    fprintf (dmp, "%16.8e %15.8e\n", rr (i), dd (i));
    }
  for (i = 0; i < no; i++) {
    pp [i].dump (dmp);
    }

  return 0;
  }
