#ifndef EBUGGED

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static char *memmsg =
  "nl_c::nl_c (%d) : error allocating memory\n";
static char *rngmsg =
  "nl_c::operator (%d, %d) : quantum number %c out of range\n";

#endif

/*
* nl_c
* orbital index
*/
#include "nl.h"

/*
* nl_c
* do-nothing constructor
*/
nl_c::nl_c (void) {
  }

/*
* nl_c
* real constructor
*/
nl_c::nl_c (int n) {

  nn = n;

  d = new int [(n+1)*(n+2)/2];

#ifndef EBUGGED
  if (d == 0) {
    fprintf (stderr, memmsg, n);
    exit (errno);
    }
#endif

  }

/*
* operator ()
* do subscripting
*/
int &nl_c::operator () (int n, int l) {

#ifndef EBUGGED
  if ((n < 0) || (n > nn)) {
    fprintf (stderr, rngmsg, n, l, (char) 'n');
    exit (-1);
    }
  if ((l < 0) || (l > n)) {
    fprintf (stderr, rngmsg, n, l, (char) 'l');
    exit (-1);
    }
#endif

  return d [n*(n+1)/2 + l];
  }
