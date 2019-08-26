#ifndef ORBITAL_H
#define ORBITAL_H

#include <stdio.h>

#include "vector.h"

class orbital_c: public vector_c {
 public:

  int n;
  int l;
  double occ [2];
  double e;

  void orbital (basis_c *);

  void guess (void);
  void dump (FILE *fd);
  };

#endif
