#ifndef BASIS_H
#define BASIS_H

class basis_c {
 public:

  int n;
  double *d;

  basis_c (void);
  basis_c (int in, double z, double x0, double xn);
  void basis (double z, double x0, double xn);

#ifdef EBUGGED
  inline double &operator () (int i) {
    return d [i+1];
    };
#else
  double &operator () (int);
#endif
  
  };

#endif
