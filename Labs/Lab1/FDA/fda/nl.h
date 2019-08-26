#ifndef NL_H
#define NL_H

class nl_c {
 public:

  int nn;
  int *d;

  nl_c (void);
  nl_c (int);

  int &operator () (int, int);
  };

#endif
