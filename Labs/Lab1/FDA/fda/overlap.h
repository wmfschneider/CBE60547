#ifndef OVERLAP_H
#define OVERLAP_H

#include "oper1.h"

class overlap_c: public oper1_c {
 public:
  overlap_c (void);
  overlap_c (basis_c *);
  void overlap (void);
  };

#endif
