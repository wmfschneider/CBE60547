#include <math.h>

#include "orbital.h"

/*
* orbital
*/
void orbital_c::orbital (basis_c *ir) {

  vector (ir);

  return;
  }

/*
* orbital_c::guess
* make an initial guess based on eigenvalue and quantum numbers
*/
void orbital_c::guess (void) {

  orbital_c &a = *this;
  basis_c &b = *r;
  double y;
  int i, ip;

  ip = n - l;

  for (i = 0; i < b.n; i++) {
    y = b (i);
    a (i) = pow (y, ip) * exp (2*e*y);
    }

  return;
  }

/*
* dump
*/
void orbital_c::dump (FILE *fd) {

  int i;

  fprintf (fd, "%8d %7d %7.4f %7.4f %15.8f\n", n, l, occ [0], occ [1], e);
  for (i = 0; i < r->n; i++) {
    fprintf (fd, "%16.8e\n", d [i]);
    }

  return;
  }
