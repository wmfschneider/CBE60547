#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static char *memmsg =
  "vector_c::%s [%d] : error allocating memory\n";
static char *rngmsg =
  "vector_c::%s (%d) : subscript %c out of range\n";
static char *basmsg =
  "vector_c::%s : vector basis mis-match\n";

/*
* vector_c
* base class for a vector defined over a given basis
*/
#include "vector.h"

/*
* vector_c
* do-nothing constructor
*/
vector_c::vector_c (void) {
  }

/*
* vector_c
* vector constructor
* a do-nothing constructor as well
* call routine to allocate memory
*/
vector_c::vector_c (basis_c *ir) {
  vector (ir);
  }

/*
* vector
* does the real work of constructing the vector
*/
void vector_c::vector (basis_c *ir) {

  static char *id = "vector (basis_c *)";

  r = ir;
  n = r->n;

  d = new double [n];

  if (d == 0) {
    fprintf (stderr, memmsg, id, n);
    exit (errno);
    }

  return;
  }

/*
* operator ()
* do subscripting
*/
#ifndef EBUGGED
double &vector_c::operator () (int i) {

  static char *id = "double &operator () (int)";

  if ((i < 0) || (i >= n)) {
    fprintf (stderr, rngmsg, id, i, (char) 'i');
    exit (-1);
    }

  return d [i];
  }
#endif

/*
* operator ^=
* set to a constant
*/
void vector_c::operator ^= (double x) {

  int i;

  for (i = 0; i < n; i++) {
    d [i] = x;
    }

  return;
  }

/*
* operator ^=
* simple vector assignment
*/
void vector_c::operator ^= (vector_c &b) {

  static char *id = "void operator ^= (vector_c &)";
  
  int i;

#ifndef EBUGGED
  if (r != b.r) {
    fprintf (stderr, basmsg, id);
    exit (-1);
    }
#endif

  for (i = 0; i < n; i++) {
    d [i] = b.d [i];
    }

  return;
  }

/*
* operator *=
* multiplication by a scalar
*/
void vector_c::operator *= (double x) {

  int i;

  for (i = 0; i < n; i++) {
    d [i] *= x;
    }

  return;
  }

/*
* operator +=
* addition of another vector
*/
void vector_c::operator += (vector_c &b) {

  static char *id = "operator += (vector_c &)";

  int i;

#ifndef EBUGGED
  if (r != b.r) {
    fprintf (stderr, basmsg, id);
    exit (-1);
    }
#endif

  for (i = 0; i < n; i++) {
    d [i] += b.d [i];
    }

  return;
  }

/*
* operator *
* inner product
*/
double vector_c::operator * (vector_c &w) {

  static char *id = "operator * (vector_c &)";

  vector_c &v = *this;
  basis_c &b = *r;
  double x, y, z;
  double L, R;
  double A, B, C;
  double s;
  int i;

#ifndef EBUGGED
  if (r != w.r) {
    fprintf (stderr, basmsg, id);
    exit (-1);
    }
#endif

  i = 0; {
    x = b (i-1); y = b (i); z = b (i+1);
    L = y - x; R = z - y;
    B = v (i) * w (i);
    A = -B;
    C = v (i+1) * w (i+1) - B;
    s = L * B / 8;
    s += (L + R) * B / 2 +
         (R*R - L*L) * (C/R - A/L) / 16 +
         (R*R - R*L + L*L) * (C/R + A/L) / 24;
    }
  for (i = 1; i < n-1; i++) {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    B = v (i) * w (i);
    A = -C;
    C = v (i+1) * w (i+1) - B; 
    s += (L + R) * B / 2 +
         (R*R - L*L) * (C/R - A/L) / 16 +
         (R*R - R*L + L*L) * (C/R + A/L) / 24;
    }
  i = n-1; {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    B = v (i) * w (i);
    A = -C;
    C = -B;
    s += (L + R) * B / 2 +
         (R*R - L*L) * (C/R - A/L) / 16 +
         (R*R - R*L + L*L) * (C/R + A/L) / 24;
    s += R * B / 8;
    }

  return s;
  }
