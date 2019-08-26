/*
* 1/r operator
*/
#include "rm1.h"

/*
* rm1_c
* do-nothing constructor
*/
rm1_c::rm1_c (void) {
  }

/*
* rm1_c
* rm1 constructor
* allocate operator with base class constructor,
* call routine to evaluate matrix elements
*/
rm1_c::rm1_c (basis_c *ir) {
  oper1 (ir);
  rm1 ();
  }

/*
* rm1
* Generate the r^(-1) operator matrix elements
*/
void rm1_c::rm1 (void) {

  rm1_c &a = *this;
  basis_c &b = *r;
  int i;

  i = 0; {
    a (i, i)   = 1.0 / b (i);
    a (i, i+1) = 0.0;
    }
  for (i = 1; i < n-1; i++) {
    a (i, i-1) = 0.0;
    a (i, i)   = 1.0 / b (i);
    a (i, i+1) = 0.0;
    }
  i = n-1; {
    a (i, i-1) = 0.0;
    a (i, i)   = 1.0 / b (i);
    }

  return;
  }
