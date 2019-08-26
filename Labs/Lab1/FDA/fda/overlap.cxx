/*
* overlap operator
*/
#include "overlap.h"

/*
* overlap_c
* do-nothing constructor
*/
overlap_c::overlap_c (void) {
  }

/*
* overlap_c
* overlap constructor
* allocate operator with base class constructor,
* call routine to evaluate matrix elements
*/
overlap_c::overlap_c (basis_c *ir) {
  oper1 (ir);
  overlap ();
  }

/*
* overlap
* Generate the overlap operator matrix elements
*/
void overlap_c::overlap (void) {

  overlap_c &a = *this;
  int i;

  a ^= 1.0;

  return;
  }
