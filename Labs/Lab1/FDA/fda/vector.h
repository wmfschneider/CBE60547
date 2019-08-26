#ifndef VECTOR_H
#define VECTOR_H

#include "basis.h"

class vector_c {
 public:

  basis_c *r;
  int n;
  double *d;

  vector_c (void);
  vector_c (basis_c *);
  void vector (basis_c *);

#ifdef EBUGGED
  inline double &operator () (int i) {
    return d [i];
    };
#else
  double &operator () (int);
#endif
  void operator ^= (double);
  void operator ^= (vector_c &);
  void operator *= (double);
  void operator += (vector_c &);
  double operator * (vector_c &);
  };

#endif
