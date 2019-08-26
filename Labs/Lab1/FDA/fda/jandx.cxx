#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897930
#endif

/*
* coulomb and exchange operator
*/
#include "jandx.h"

/*
* jandx_c
* do-nothing constructor
*/
jandx_c::jandx_c (void) {
  }

/*
* jandx_c
* jandx constructor
* allocate operator with base class constructor
*/
jandx_c::jandx_c (basis_c *ir) {
  oper1 (ir);
  }

/*
* jandx
* Generate the Coulomb and Exchange operator matrix elements
*/
void jandx_c::jandx (double alpha, double beta, double ze, densityx_c &p) {

  jandx_c &a = *this;
  basis_c &b = *r;

  double i3, den, fac;
  double x, y, z;
  double L, R;
  double A, B, C;
  int i, j;

  a ^= 0.0;
/*
* first pass, coulomb with r2 < r1
*/
  i = 0; {
    x = b (i-1); y = b (i); z = b (i+1);
    L = y - x; R = z - y;
    B = p (i, i);
    A = -B;
    C = p (i+1, i+1) - B;
    den = L * B / 8;
    den += L * B / 2 -
           L*L * (C/R - A/L) / 16 +
           L*L*L * (C/R + A/L) / (24*(R+L));
    a (i, i) = den / y;
    den += R * B / 2 +
           R*R * (C/R - A/L) / 16 +
           R*R*R * (C/R + A/L) / (24*(R+L));
    }
  for (i = 1; i < n-1; i++) {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    B = p (i, i);
    A = -C;
    C = p (i+1, i+1) - B;
    den += L * B / 2 -
           L*L * (C/R - A/L) / 16 +
           L*L*L * (C/R + A/L) / (24*(R+L));
    a (i, i) = den / y;
    den += R * B / 2 +
           R*R * (C/R - A/L) / 16 +
           R*R*R * (C/R + A/L) / (24*(R+L));
    }
  i = n-1; {
    x = y; y = z; z = b (i+1);
    L = R; R = z - y;
    B = p (i, i);
    A = -C;
    C = -B;
    den += L * B / 2 -
           L*L * (C/R - A/L) / 16 +
           L*L*L * (C/R + A/L) / (24*(R+L));
    a (i, i) = den / y;
    }

/*
* second pass, coulomb with r2 > r1
*/
  i = n-1; {
    z = b (i+1); y = b (i); x = b (i-1);
    R = z - y; L = y - x;
    B = p (i, i) / y;
    C = -B;
    A = p (i-1, i-1) / x - B;
    den = R * B / 8;
    den += R * B / 2 +
           R*R * (C/R - A/L) / 16 +
           R*R*R * (C/R + A/L) / (24*(R+L));
    a (i, i) += den;
    den += L * B / 2 -
           L*L * (C/R - A/L) / 16 +
           L*L*L * (C/R + A/L) / (24*(R+L));
    }
  for (i = n-2; i > 0; i--) {
    z = y; y = x; x = b (i-1);
    R = L; L = y - x;
    B = p (i, i) / y;
    C = -A;
    A = p (i-1, i-1) / x - B;
    den += R * B / 2 +
           R*R * (C/R - A/L) / 16 +
           R*R*R * (C/R + A/L) / (24*(R+L));
    a (i, i) += den;
    den += L * B / 2 -
           L*L * (C/R - A/L) / 16 +
           L*L*L * (C/R + A/L) / (24*(R+L));
    }
  i = 0; {
    z = y; y = x; x = b (i-1);
    R = L; L = y - x;
    B = p (i, i) / y;
    C = -A;
    A = -B;
    den += R * B / 2 +
           R*R * (C/R - A/L) / 16 +
           L*R*R * (C/R + A/L) / (24*(R+L));
    a (i, i) += den;
    }

/*
* third pass, do exchange
*/
  i3 = 1.0 / 3.0;
  fac = 3 * fabs (alpha) * pow (3 / (8 * M_PI * M_PI), i3);

  for (i = 0; i < n; i++) {
    y = b (i);
    a (i, i) -= fac * pow (p (i, i) / (y * y), i3);
    }

/*
* fourth pass, correct potential for large r
*/
  if (alpha > 0.0) {
    ze -= 1.0;
    if (ze < 0.0) ze = 0.0;
    for (i = n-1; i >= 0; i--) {
      if (a (i, i) < ze / b (i)) break;
      a (i, i) = ze / b (i);
      }
    }

  return;
  }
