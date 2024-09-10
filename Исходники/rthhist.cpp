extern "C" SEXP rthhist(SEXP x, SEXP nbins_,  SEXP nch_, SEXP nthreads)
{
  const int n = LENGTH(x);
  const int nbins = INTEGER(nbins_)[0];
  const int nch = INTEGER(nch_)[0];
  
  floublevec dx(REAL(x), REAL(x)+n);
  
  SEXP bincounts, R_left, R_binwidth;
  PROTECT(bincounts = allocVector(INTSXP, nbins));
  PROTECT(R_left = allocVector(REALSXP, 1));
  PROTECT(R_binwidth = allocVector(REALSXP, 1));
  
  SEXP ret, retnames;
  
  RTH_GEN_NTHREADS(nthreads);
  
  // determine binwidth etc.
  thrust::pair<floubleveciter, floubleveciter> mm = 
    thrust::minmax_element(dx.begin(), dx.end());
  flouble left = *(mm.first), right = *(mm.second);
  flouble binwidth = (right - left) / nbins;
  
  // form matrix of bin counts, one row per chunk
  intvec dbincounts(nch*nbins);
  
  
  // the heart of the computation, a for_each() loop, one iteration per
  // chunk
  thrust::counting_iterator<int> seqa(0);
  thrust::counting_iterator<int> seqb =  seqa + nch;
  thrust::for_each(seqa,seqb,
    do1chunk(dx.begin(),dbincounts.begin(
      
    ), n, nbins, nch, left, binwidth));
  
  // copy result to host and combine the subhistograms
  int hbincounts[nch*nbins];
  thrust::copy(dbincounts.begin(), dbincounts.end(), hbincounts);
  int binnum,chunknum;
  for (binnum = 0; binnum < nbins; binnum++) {
    int sum = 0;
    for (chunknum = 0; chunknum < nch; chunknum++) 
      sum += hbincounts[chunknum*nbins + binnum];
    INTEGER(bincounts)[binnum] = sum;
  }
  
  
  REAL(R_left)[0] = (double) left; 
  REAL(R_binwidth)[0] = (double) binwidth;
  
  PROTECT(retnames = allocVector(STRSXP, 3));
  SET_STRING_ELT(retnames, 0, mkChar("counts"));
  SET_STRING_ELT(retnames, 1, mkChar("left"));
  SET_STRING_ELT(retnames, 2, mkChar("binwidth"));
  
  PROTECT(ret = allocVector(VECSXP, 3));
  SET_VECTOR_ELT(ret, 0, bincounts);
  SET_VECTOR_ELT(ret, 1, R_left);
  SET_VECTOR_ELT(ret, 2, R_binwidth);
  
  setAttrib(ret, R_NamesSymbol, retnames);
  
  UNPROTECT(5);
  return ret;
}