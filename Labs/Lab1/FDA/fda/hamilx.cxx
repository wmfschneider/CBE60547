/*
* hamilx operator
*/
#include "hamilx.h"

/*
* hamilx_c
* do-nothing constructor
*/
hamilx_c::hamilx_c (void) {
  }

/*
* hamilx_c
* the hamilx constructor
*/
hamilx_c::hamilx_c (basis_c *ir) {
  oper1 (ir);
  }

/*
* hamilx
* Generate the hamiltonian matrix elements
*/
void hamilx_c::hamilx (del2_c &ke, double zn, rm1_c &vn, int l, rm2_c &va, jandx_c &jk) {

  hamilx_c &ha = *this;
  int i;

  l = l * (l + 1) / 2;

  i = 0; {
    ha (i, i)   = -0.5*ke (i, i)   - zn*vn (i, i)   + l*va (i, i)   + jk (i, i);
    ha (i, i+1) = -0.5*ke (i, i+1) - zn*vn (i, i+1) + l*va (i, i+1) + jk (i, i+1);
    }
  for (i = 1; i < n-1; i++) {
    ha (i, i-1) = -0.5*ke (i, i-1) - zn*vn (i, i-1) + l*va (i, i-1) + jk (i, i-1);
    ha (i, i)   = -0.5*ke (i, i)   - zn*vn (i, i)   + l*va (i, i)   + jk (i, i);
    ha (i, i+1) = -0.5*ke (i, i+1) - zn*vn (i, i+1) + l*va (i, i+1) + jk (i, i+1);
    }
  i = n-1; {
    ha (i, i-1) = -0.5*ke (i, i-1) - zn*vn (i, i-1) + l*va (i, i-1) + jk (i, i-1);
    ha (i, i)   = -0.5*ke (i, i)   - zn*vn (i, i)   + l*va (i, i)   + jk (i, i);
    }

  return;
  }
