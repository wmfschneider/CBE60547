#ifndef HAMILX_H
#define HAMILX_H

#include "oper1.h"
#include "del2.h"
#include "rm1.h"
#include "rm2.h"
#include "jandx.h"

class hamilx_c: public oper1_c {
 public:
  hamilx_c (void);
  hamilx_c (basis_c *);
  void hamilx (del2_c &, double, rm1_c &, int, rm2_c &, jandx_c &);
  };

#endif
