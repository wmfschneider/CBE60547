/*
* r operator
*/
#include "rp1.h"

/*
* rp1_c
* do-nothing constructor
*/
rp1_c::rp1_c (void) {
  }

/*
* rp1_c
* rp1 constructor
* allocate operator with base class constructor,
* call routine to evaluate matrix elements
*/
rp1_c::rp1_c (basis_c *ir) {
  oper1 (ir);
  rp1 ();
  }

/*
* rp1
* Generate the r^(+1) operator matrix elements
*/
void rp1_c::rp1 (void) {

  rp1_c &a = *this;
  basis_c &b = *r;
  int i;

  i = 0; {
    a (i, i)   = b (i);
    a (i, i+1) = 0.0;
    }
  for (i = 1; i < n-1; i++) {
    a (i, i-1) = 0.0;
    a (i, i)   = b (i);
    a (i, i+1) = 0.0;
    }
  i = n-1; {
    a (i, i-1) = 0.0;
    a (i, i)   = b (i);
    }

  return;
  }
