#ifndef DEL2_H
#define DEL2_H

#include "oper1.h"

/*
* the second derivative operator
*/
class del2_c: public oper1_c {
 public:
  del2_c (void);
  del2_c (basis_c *);
  void del2 (void);
  };

#endif
