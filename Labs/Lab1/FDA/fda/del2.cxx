/*
* second derivative operator
*/
#include "del2.h"

/*
* del2_c
* do-nothing constructor
*/
del2_c::del2_c (void) {
  }

/*
* del2_c
* del2 constructor
* allocate operator with base class constructor,
* call routine to evaluate matrix elements
*/
del2_c::del2_c (basis_c *ir) {
  oper1 (ir);
  del2 ();
  }

/*
* del2
* Generate the second derivative operator matrix elements
*/
void del2_c::del2 (void) {

  del2_c &a = *this;
  basis_c &b = *r;
  double x, y, z;
  double L, R;
  int i;

  i = 0; {
    x = b (i-1); y = b (i); z = b (i+1);
    L = y - x; R = z - y;
    a (i, i)   = -2.0 / (L*R);
    a (i, i+1) =  2.0 / (R*(L+R));
    }
  for (i = 1; i < n-1; i++) {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    a (i, i-1) =  2.0 / (L*(L+R));
    a (i, i)   = -2.0 / (L*R);
    a (i, i+1) =  2.0 / (R*(L+R));
    }
  i = n-1; {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    a (i, i-1) =  2.0 / (L*(L+R));
    a (i, i)   = -2.0 / (L*R);
    }

  return;
  }
