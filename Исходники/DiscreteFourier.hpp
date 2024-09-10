inline void
MakeDiscreteFourier( Matrix<Complex<R> >& A )
{
#ifndef RELEASE
    CallStackEntry entry("MakeDiscreteFourier");
#endif
    typedef Complex<R> F;

    const int m = A.Height();
    const int n = A.Width();
    if( m != n )
        throw std::logic_error("Cannot make a non-square DFT matrix");

    const R pi = 4*Atan( R(1) );
    const F nSqrt = Sqrt( R(n) );
    for( int j=0; j<n; ++j )
    {
        for( int i=0; i<m; ++i )
        {
            const R theta = -2*pi*i*j/n;
            A.Set( i, j, Complex<R>(Cos(theta),Sin(theta))/nSqrt );
        }
    }
}