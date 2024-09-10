inline void
MakeKahan( F phi, DistMatrix<F,U,V>& A )
{
#ifndef RELEASE
    PushCallStack("MakeKahan");
#endif
    typedef typename Base<F>::type R;

    const int m = A.Height();
    const int n = A.Width();
    if( m != n )
        throw std::logic_error("Cannot make a non-square matrix Kahan");
    if( Abs(phi) >= R(1) )
        throw std::logic_error("Phi must be in (0,1)");

    const F zeta = Sqrt(1-phi*Conj(phi));

    const int localHeight = A.LocalHeight();
    const int localWidth = A.LocalWidth();
    const int colShift = A.ColShift();
    const int rowShift = A.RowShift();
    const int colStride = A.ColStride();
    const int rowStride = A.RowStride();
    for( int iLocal=0; iLocal<localHeight; ++iLocal )
    {
        const int i = colShift + iLocal*colStride;
        const F zetaPow = Pow( zeta, R(i) );
        for( int jLocal=0; jLocal<localWidth; ++jLocal )
        {
            const int j = rowShift + jLocal*rowStride;
            if( i > j )       
                A.SetLocal( iLocal, jLocal, F(0) ); 
            else if( i == j )
                A.SetLocal( iLocal, jLocal, zetaPow );
            else
                A.SetLocal( iLocal, jLocal, -phi*zetaPow );
        }
    }
#ifndef RELEASE
    PopCallStack();
#endif
}