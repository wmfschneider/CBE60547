#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

/*
* some error messages
*/
static char *memmsg =
  "oper1_c::%s : error allocating memory [%d]\n";
static char *rngmsg =
  "oper1_c::%s (%d, %d) : subscript out of range\n";
static char *oprmsg =
  "oper1_c::%s : operator basis mis-match\n";
static char *vecmsg =
  "oper1_c::%s : vector basis mis-match\n";
static char *wkvmsg =
  "oper1_c::%s : erorr allocating work-space vector\n";
static char *eigmsg =
  "oper1_c::%s : didn't converge in eigenvector refinement\n";

/*
* oper1_c
* base class for a tri-diagonal 1-particle operator
*/
#include "oper1.h"

/*
* oper1_c
* do-nothing constructor
*/
oper1_c::oper1_c (void) {
  }

/*
* oper1_c
* oper1 constructor
* a do-nothing constructor as well, this would only be
*   invoked if a generic operator were instantiated
* call routine to allocate memory and initialize pointers
*/
oper1_c::oper1_c (basis_c *ir) {
  oper1 (ir);
  }

/*
* oper1
* does the real work of contructing the operator
*/
void oper1_c::oper1 (basis_c *ir) {

  static char *id = "oper1 (basis_c *)";

  r = ir;
  n = r->n;
  wkv = 0;

  d = new double [3*n-2];
  if (d == 0) {
    fprintf (stderr, memmsg, id, n);
    exit (errno);
    }

  return;
  }

/*
* all_wkv
* utility routine to allocate work vector
*/
void oper1_c::all_wkv (char *id) {
  if (wkv == 0) {
    wkv = new vector_c (r);
    if (wkv == 0) {
      fprintf (stderr, wkvmsg, id);
      exit (-1);
      }
    }
  return;
  }
 
/*
* operator ()
* do subscripting
*/
#ifndef EBUGGED
double &oper1_c::operator () (int i, int j) {

  static char *id = "double &operator () (int, int)";
  int I, J;

  I = i; J = j;
  if (j > i) {
    I = j; J = i;
    }
  if ((J < 0) || (I >=n) || (I-J > 1)) {
    fprintf (stderr, rngmsg, id, i, j);
    exit (-1);
    }
 
  return d [2*i+j];
  }
#endif

/*
* operator ^=
* set to a multiple of the unit matrix
*/
void oper1_c::operator ^= (double x) {

  oper1_c &a = *this;
  int i;

  i = 0; {
    a (i, i)   = x;
    a (i, i+1) = 0.0;
    }
  for (i = 1; i < n-1; i++) {
    a (i, i-1) = 0.0;
    a (i, i)   = x;
    a (i, i+1) = 0.0;
    }
  i = n-1; {
    a (i, i-1) = 0.0;
    a (i, i)   = x;
    }

  return;
  }

/*
* operator ^=
* simple operator assignment
*/
void oper1_c::operator ^= (oper1_c &b) {
 
  static char *id = "operator ^= (oper1_c &)";
 
  int i;
 
#ifndef EBUGGED
  if (r != b.r) {
    fprintf (stderr, oprmsg, id);
    exit (-1);
    }
#endif
 
  for (i = 0; i < 3*n-2; i++) {
    d [i] = b.d [i];
    }

  return;
  }

/*
* operator *=
* multiplication by a scalar
*/
void oper1_c::operator *= (double x) {

  int i;

  for (i = 0; i < 3*n-2; i++) {
    d [i] *= x;
    }

  return;
  }

/*
* operator +=
* addition of another operator
*/
void oper1_c::operator += (oper1_c &b) {

  static char *id = "void operator += (oper1_c &)";

  int i;

#ifndef EBUGGED
  if (r != b.r) {
    fprintf (stderr, oprmsg, id);
    exit (-1);
    }
#endif

  for (i = 0; i < 3*n-2; i++) {
    d [i] += b.d [i];
    }

  return;
  }

/*
* operator *=
* operate on a vector
*/
void oper1_c::operator *= (vector_c &v) {

  static char *id = "void operator *= (vector_c &)";

  oper1_c &a = *this;
  double A, B, C;
  int i;

#ifndef EBUGGED
  if (r != v.r) {
    fprintf (stderr, oprmsg, id);
    exit (-1);
    }
#endif

  i = 0; {
    B = v (i); C = v (i+1);
    v (i) = a (i, i) * B + a (i, i+1) * C;
    }
  for (i = 1; i < n-1; i++) {
    A = B; B = C; C = v (i+1);
    v (i) = a (i, i-1) * A + a (i, i) * B + a (i, i+1) * C;
    }
  i = n-1; {
    A = B; B = C;
    v (i) = a (i, i-1) * A + a (i, i) * B;
    }

  return;
  }

/*
* gdot
* generalized dot product of two vectors
*/
double oper1_c::gdot (vector_c &u, vector_c &v) {

  static char *id = "double gdot (vector_c &, vector_c &)";

  oper1_c &a = *this;
  double s;
  int i;

#ifndef EBUGGED
  if ((r != u.r) || (r != v.r)) {
    fprintf (stderr, vecmsg, id);
    exit (-1);
    }
#endif

  all_wkv (id);
  vector_c &w = *wkv;

  w ^= v;
  a *= w;
  s = u * w;

  return s;
  }

/*
* geigen
* improve a trial eigenvector and eigenvalue of A - e.S using lu method
*/
double oper1_c::geigen (double cnv, double e, oper1_c &s, vector_c &v) {

  static char *id = "double geigen (double, double, oper1_c &, vector_c &)";

  oper1_c &a = *this;
  double e0, th, ti, al, au, z;
  int maxitr, itr, i;

#ifndef EBUGGED
  if (r != s.r) {
    fprintf (stderr, oprmsg, id);
    exit (-1);
    }
#endif

#ifndef EBUGGED
  if (r != v.r) {
    fprintf (stderr, vecmsg, id);
    exit (-1);
    }
#endif

  all_wkv (id);
  vector_c &w = *wkv;

/*
* repeat until eigenvalue is converged
*/
  maxitr = (int) ceil (log (cnv) / log (0.5));
  for (itr = 0; itr < maxitr; itr++) {
    e0 = e;

/*
* solve for new eigenvector using combined lu decomposition
* and forward/backward substitution
*/
    ti = a (0, 0) - e * s (0, 0);
    z = 1.0;
    v (0) /= ti;
    for (i = 1; i < n; i++) {
      th = ti; ti = a (i, i) - e * s (i, i);
      au = a (i-1, i) - e * s (i-1, i);
      al = a (i, i-1) - e * s (i, i-1);
      w (i) = au / (z * th);
      z = 1.0 - al * w (i) / ti;
      v (i) = (v (i) - al * v (i-1)) / (z * ti);
      }
    for (i = n-2; i >= 0; i--) {
      v (i) -= w (i+1) * v (i+1);
      }

/*
* normalize and find eigenvalue, check convergence
*/
    z = 1.0 / sqrt (s.gdot (v, v));
    v *= z;
    e = gdot (v, v);
    if (fabs (e - e0) < fabs (e0 * cnv)) break;
    }

/*
* did the eigenvalue converge?
*/
  if (itr >= maxitr) {
    fprintf (stderr, eigmsg, id);
    }

  return e;
  }
