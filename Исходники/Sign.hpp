inline void
NewtonStep
( const DistMatrix<F>& X, DistMatrix<F>& XNew, Scaling scaling=FROB_NORM )
{
#ifndef RELEASE
    CallStackEntry entry("sign::NewtonStep");
#endif
    typedef BASE(F) Real;

    // Calculate mu while forming B := inv(X)
    Real mu;
    DistMatrix<Int,VC,STAR> p( X.Grid() );
    XNew = X;
    LU( XNew, p );
    if( scaling == DETERMINANT )
    {
        SafeProduct<F> det = determinant::AfterLUPartialPiv( XNew, p );
        mu = Real(1)/Exp(det.kappa);
    }
    inverse::AfterLUPartialPiv( XNew, p );
    if( scaling == FROB_NORM )
        mu = Sqrt( FrobeniusNorm(XNew)/FrobeniusNorm(X) );
    else if( scaling == NONE )
        mu = 1;
    else
        LogicError("Scaling case not handled");

    // Overwrite XNew with the new iterate
    const Real halfMu = mu/Real(2);
    const Real halfMuInv = Real(1)/(2*mu); 
    Scale( halfMuInv, XNew );
    Axpy( halfMu, X, XNew );
}