void FoxLi( ElementalMatrix<Complex<Real>>& APre, Int n, Real omega )
{
    DEBUG_CSE
    typedef Complex<Real> C;
    const Real pi = 4*Atan( Real(1) );
    const C phi = Sqrt( C(0,omega/pi) ); 

    DistMatrixWriteProxy<C,C,MC,MR> AProx( APre );
    auto& A = AProx.Get();
    
    // Compute Gauss quadrature points and weights
    const Grid& g = A.Grid();
    DistMatrix<Real,VR,STAR> d(g), e(g); 
    Zeros( d, n, 1 );
    e.Resize( n-1, 1 );
    auto& eLoc = e.Matrix();
    for( Int iLoc=0; iLoc<e.LocalHeight(); ++iLoc )
    {
        const Int i = e.GlobalRow(iLoc);
        const Real betaInv = 2*Sqrt(1-Pow(i+Real(1),-2)/4);
        eLoc(iLoc) = 1/betaInv;
    }
    DistMatrix<Real,VR,STAR> x(g);
    DistMatrix<Real,STAR,VR> Z(g);
    HermitianTridiagEig( d, e, x, Z, UNSORTED );
    auto z = Z( IR(0), ALL );
    DistMatrix<Real,STAR,VR> sqrtWeights( z );
    auto& sqrtWeightsLoc = sqrtWeights.Matrix();
    for( Int jLoc=0; jLoc<sqrtWeights.LocalWidth(); ++jLoc )
        sqrtWeightsLoc(0,jLoc) = Sqrt(Real(2))*Abs(sqrtWeightsLoc(0,jLoc));
    herm_eig::Sort( x, sqrtWeights, ASCENDING );

    // Form the integral operator
    A.Resize( n, n );
    DistMatrix<Real,MC,STAR> x_MC( A.Grid() );
    DistMatrix<Real,MR,STAR> x_MR( A.Grid() );
    x_MC.AlignWith( A ); 
    x_MR.AlignWith( A );
    x_MC = x;
    x_MR = x;
    auto& ALoc = A.Matrix();
    auto& x_MCLoc = x_MC.Matrix();
    auto& x_MRLoc = x_MR.Matrix();
    for( Int jLoc=0; jLoc<A.LocalWidth(); ++jLoc )
    {
        for( Int iLoc=0; iLoc<A.LocalHeight(); ++iLoc )
        {
            const Real diff = x_MCLoc(iLoc)-x_MRLoc(jLoc);
            const Real theta = -omega*Pow(diff,2);
            const Real realPart = Cos(theta);
            const Real imagPart = Sin(theta);
            ALoc(iLoc,jLoc) = phi*C(realPart,imagPart);
        }
    }

    // Apply the weighting
    DistMatrix<Real,VR,STAR> sqrtWeightsTrans(g);
    Transpose( sqrtWeights, sqrtWeightsTrans );
    DiagonalScale( LEFT, NORMAL, sqrtWeightsTrans, A );
    DiagonalScale( RIGHT, NORMAL, sqrtWeightsTrans, A );
}