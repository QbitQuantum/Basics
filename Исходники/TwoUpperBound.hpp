TwoNormUpperBound( const DistMatrix<F>& A )
{
#ifndef RELEASE
    CallStackEntry entry("TwoNormUpperBound");
#endif
    typedef BASE(F) R;
    const R m = A.Height();
    const R n = A.Width();

    const R maxNorm = MaxNorm( A );
    const R oneNorm = OneNorm( A );
    const R infNorm = InfinityNorm( A );

    R upperBound = std::min( Sqrt(m*n)*maxNorm, Sqrt(m)*infNorm );
    upperBound = std::min( upperBound, Sqrt(n)*oneNorm );
    upperBound = std::min( upperBound, Sqrt( oneNorm*infNorm ) );
    return upperBound;
}