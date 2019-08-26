/*
* 1/r^2 operator
*/
#include "rm2.h"

/*
* rm2_c
* do-nothing constructor
*/
rm2_c::rm2_c (void) {
  }

/*
* rm2_c
* rm2 constructor
* allocate operator with base class constructor,
* call routine to evaluate matrix elements
*/
rm2_c::rm2_c (basis_c *ir) {
  oper1 (ir);
  rm2 ();
  }

/*
* rm2
* Generate the r^(-2) operator matrix elements
*/
void rm2_c::rm2 (void) {

  rm2_c &a = *this;
  basis_c &b = *r;
  int i;

  i = 0; {
    a (i, i)   = 1.0 / (b (i) * b (i));
    a (i, i+1) = 0.0;
    }
  for (i = 1; i < n-1; i++) {
    a (i, i-1) = 0.0;
    a (i, i)   = 1.0 / (b (i) * b (i));
    a (i, i+1) = 0.0;
    }
  i = n-1; {
    a (i, i-1) = 0.0;
    a (i, i)   = 1.0 / (b (i) * b (i));
    }

  return;
  }
