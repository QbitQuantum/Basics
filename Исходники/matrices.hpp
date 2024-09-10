matrix<T> gemm( const matrix<T> &a, const char transa, const matrix<T> &\
	   b, const char transb)
{
  int M = ( (transa=='N')||(transa=='n') ) ? a.nrow : a.ncol;
  int N = ( (transb=='N')||(transb=='n') ) ? b.ncol : b.nrow;
  int K = ( (transa=='N')||(transa=='n') ) ? a.ncol : a.nrow;
  int Kcheck = ( (transb=='N')||(transb=='n') ) ? b.nrow : b.ncol;

  matrix<T> result(M,N);
  /* check for dimension errors */
  if ( (K != Kcheck) )
    _ERROR_("incompatible matrices",result);

  matrix<T> c1(M,K),c2(K,N);
  
  if ( ( (transa=='N')||(transa=='n') ) )
    c1 = a;
  else if ( ( (transa=='T')||(transa=='t') ) )
    c1 = a.transpose();
  else
    c1 = a.daga();


  if ( ( (transb=='N')||(transb=='n') ) )
    c2 = b;
  else if ( ( (transb=='T')||(transb=='t') ) )
    c2 = b.transpose();
  else
    c2 = b.daga();

  result = 0.0;
  
  for (int irow=0;irow<M;++irow)
    for (int icol=0;icol<N;++icol)
      for (int ik=0;ik<K;++ik)
	result(irow,icol) += c1.pointer[c1.index(irow,ik)]*c2.pointer[c2.index(ik,icol)];

  return result;
}