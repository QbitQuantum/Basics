SEXP qorder(SEXP data)
{
  R_xlen_t n = Rf_xlength(data);

  // Rprintf("qorder: length of input data is %ld.\n", n);

  double * x = REAL(data);

  orderStructure * os = Calloc((size_t) n, orderStructure);

  qorder_internal(x, (size_t) n, os);

  SEXP ans;
  if (n<(size_t) 0x80000000)
  {
    // Rprintf("..returning integer order.\n");
    PROTECT (ans = allocVector(INTSXP, n));
    int * ansp = INTEGER(ans);
    for (R_xlen_t i = 0; i<n; i++) ansp[i] = (int) ( (os+i)->index+1);
  } else {
    // Rprintf("..returning floating point (double) order.\n");
    PROTECT (ans = allocVector(REALSXP, n));
    double * ansp = REAL(ans);
    for (R_xlen_t i = 0; i<n; i++) ansp[i] = (double) ((os+i)->index+1);
  }
  Free(os);
  UNPROTECT(1);
  return ans;
}