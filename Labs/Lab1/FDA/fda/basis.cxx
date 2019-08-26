#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#ifndef HAVE_LOG1P
#define log1p(x) (log (1.0 + (x)))
#endif

static char *memmsg =
  "basis_c::%s [%d] : error allocating memory\n";
static char *rngmsg =
  "basis_c::%s (%d) : subscript %c out of range\n";

/*
* basis_c
* defines the computational space
*/
#include "basis.h"

/*
* basis_c
* do-nothing constructor
*/
basis_c::basis_c (void) {
  }

/*
* basis_c
* basis constructor
* allocates memory and calls the routine that generates points
*/
basis_c::basis_c (int in, double z, double x0, double xn) {

  static char *id = "basis_c (int, double, double)";

  d = new double [in+2];

  if (d == 0) {
    fprintf (stderr, memmsg, id, in);
    exit (errno);
    }

  n = in;

  basis (z, x0, xn);

  return;
  }

/*
* basis
* Generates a geometric mesh of n+2 points with
*   point -1 at origin
*   point  0 at x0/z^1/3
*   point  n at xn*z^1/3
*/
void basis_c::basis (double z, double x0, double xn) {

  double xx, tx;
  double beta0, beta, beta1, lbetap1, hb, hb0;
  int i;

/*
* search for 1.0 + beta, the interval expansion factor
*/
  z = pow (z, 1.0/3.0);
  x0 /= z;
  xn *= z;
  xx = xn / x0;
  beta0 = 0.0;
  beta1 = pow (xx + 1.0, 1.0 / n) - 1.0;

  hb = beta1 - beta0; hb0 = 2 * hb;
  tx = 0.0;
  while ((hb < hb0) && (tx != xx)) {
    hb0 = hb;
    beta = (beta0 + beta1) / 2;
    lbetap1 = log1p (beta);
    tx = (exp (n * lbetap1) - 1.0) / beta;
    if (tx < xx)
      beta0 = beta;
    else
      beta1 = beta;
    hb = beta1 - beta0;
    }

/*
* generate the mesh points
*/
  i = -1;
  d [i+1] = 0.0;
  for (i = 0; i <= n; i++) {
    d [i+1] = x0 * (exp ((i+1) * lbetap1) - 1.0) / beta;
    }

  return;
  }

/*
* operator ()
* do subscripting
*/
#ifndef EBUGGED
double &basis_c::operator () (int i) {

  static char *id = "double &operator () (int)";

  if ((i < -1) || (i > n)) {
    fprintf (stderr, rngmsg, id, i, (char) 'i');
    exit (-1);
    }

  return d [i+1];
  }
#endif
