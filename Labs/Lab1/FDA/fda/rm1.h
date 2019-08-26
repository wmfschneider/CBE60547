#ifndef RM1_H
#define RM1_H

#include "oper1.h"

class rm1_c: public oper1_c {
 public:
  rm1_c (void);
  rm1_c (basis_c *);
  void rm1 (void);
  };

#endif
