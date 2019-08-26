#ifndef DENSITYX_H
#define DENSITYX_H

#include "oper1.h"
#include "orbital.h"

class densityx_c: public oper1_c {
 public:
  densityx_c (void);
  densityx_c (basis_c *);
  void densityx (int, int, orbital_c []);
  };

#endif
