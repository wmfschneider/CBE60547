#include "densityx.h"

/*
* densityx_c
* do-nothing constructor
*/
densityx_c::densityx_c (void) {
  }

/*
* densityx_c
* densityx constructor
* allocate operator with base class constructor
*/
densityx_c::densityx_c (basis_c *ir) {
  oper1 (ir);
  }

/*
* densityx
* Generate the densityx matrix operator matrix elements
*/
void densityx_c::densityx (int no, int spin, orbital_c orbitals []) {

  densityx_c &a = *this;
  double socc;
  int i, j;

  a ^= 0.0;
  for (j = 0; j < no; j++) {
    socc = orbitals [j].occ [0] + orbitals [j].occ [1];
    for (i = 0; i < n; i++) {
      a (i, i)   += socc * orbitals [j] (i) * orbitals [j] (i);
      }
    }

  return;
  }
