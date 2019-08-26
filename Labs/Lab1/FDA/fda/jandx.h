#ifndef JANDX_H
#define JANDX_H

#include "oper1.h"
#include "densityx.h"
#include "overlap.h"
#include "rm1.h"

class jandx_c: public oper1_c {
 public:
  jandx_c (void);
  jandx_c (basis_c *);
  void jandx (double alpha, double beta, double ze, densityx_c &p);
  };

#endif
