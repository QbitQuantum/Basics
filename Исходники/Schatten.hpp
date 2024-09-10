inline typename Base<F>::type
SymmetricSchattenNorm
( UpperOrLower uplo, const Matrix<F>& A, typename Base<F>::type p )
{
#ifndef RELEASE
    PushCallStack("SymmetricSchattenNorm");
#endif
    typedef typename Base<F>::type R;
    Matrix<F> B( A );
    Matrix<R> s;
    MakeSymmetric( uplo, B );
    SVD( B, s );

    // TODO: Think of how to make this more stable
    const int k = s.Height();
    R sum = 0;
    for( int j=0; j<k; ++j )
        sum += Pow( s.Get(j,0), p );
    const R norm = Pow( sum, 1/p );
#ifndef RELEASE
    PopCallStack();
#endif
    return norm;
}