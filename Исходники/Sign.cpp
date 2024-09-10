Int
Newton( DistMatrix<Field>& A, const SignCtrl<Base<Field>>& ctrl )
{
    EL_DEBUG_CSE
    typedef Base<Field> Real;
    Real tol = ctrl.tol;
    if( tol == Real(0) )
        tol = A.Height()*limits::Epsilon<Real>();

    Int numIts=0;
    DistMatrix<Field> B( A.Grid() );
    DistMatrix<Field> *X=&A, *XNew=&B;
    while( numIts < ctrl.maxIts )
    {
        // Overwrite XNew with the new iterate
        NewtonStep( *X, *XNew, ctrl.scaling );

        // Use the difference in the iterates to test for convergence
        Axpy( Real(-1), *XNew, *X );
        const Real oneDiff = OneNorm( *X );
        const Real oneNew = OneNorm( *XNew );

        // Ensure that X holds the current iterate and break if possible
        ++numIts;
        std::swap( X, XNew );
        if( ctrl.progress && A.Grid().Rank() == 0 )
            cout << "after " << numIts << " Newton iter's: "
                 << "oneDiff=" << oneDiff << ", oneNew=" << oneNew
                 << ", oneDiff/oneNew=" << oneDiff/oneNew << ", tol="
                 << tol << endl;
        if( oneDiff/oneNew <= Pow(oneNew,ctrl.power)*tol )
            break;
    }
    if( X != &A )
        A = *X;
    return numIts;
}