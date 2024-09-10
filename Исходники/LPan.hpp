  Matrix<F>& G )
{
    DEBUG_CSE
    const Int nU = U.Width();
    const Int n = A.Height();
    DEBUG_ONLY(
      if( nU >= n )            
          LogicError("V is too wide for the panel factorization");
      if( U.Height() != A.Height() )
          LogicError("U must be the same height as A");
      if( V.Height() != A.Height() )
          LogicError("V must be the same height as A");
      if( V.Width() != nU )
          LogicError("V must be the same width as U");
    )
    const Int phaseHeight = Max(nU,0);
    phase.Resize( phaseHeight, 1 );

    Zeros( U, n, nU );
    Zeros( V, n, nU );
    Zeros( G, nU, nU );

    Matrix<F> y10;

    for( Int k=0; k<nU; ++k )
    {
        const Range<Int> ind0( 0,   k   ),
                         ind1( k,   k+1 ),
                         ind2( k+1, n   );

        auto a12 = A( ind1, ind2    );