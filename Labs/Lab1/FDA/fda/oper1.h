#ifndef OPER1_H
#define OPER1_H

#include <stdio.h>

#include "basis.h"
#include "vector.h"

class oper1_c {
 public:

  basis_c *r;
  int n;
  double *d;

  vector_c *wkv;

  oper1_c (void);
  oper1_c (basis_c *);
  void oper1 (basis_c *);

  void all_wkv (char *);

#ifdef EBUGGED
  inline double &operator () (int i, int j) {
    return d [2*i+j];
    };
#else
  double &operator () (int, int);
#endif
  void operator ^= (double);
  void operator ^= (oper1_c &);
  void operator *= (double);
  void operator *= (vector_c &);
  void operator += (oper1_c &);

  double gdot (vector_c &, vector_c &);
  double geigen (double, double, oper1_c &, vector_c &);
  };

#endif
