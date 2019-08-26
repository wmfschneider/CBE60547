#ifndef RP1_H
#define RP1_H

#include "oper1.h"

class rp1_c: public oper1_c {
 public:
  rp1_c (void);
  rp1_c (basis_c *);
  void rp1 (void);
  };

#endif
