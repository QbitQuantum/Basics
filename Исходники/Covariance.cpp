void Covariance
( const ElementalMatrix<F>& DPre, ElementalMatrix<F>& SPre )
{
    DEBUG_CSE

    DistMatrixReadProxy<F,F,MC,MR>
      DProx( DPre );
    DistMatrixWriteProxy<F,F,MC,MR>
      SProx( SPre );
    auto& D = DProx.GetLocked();
    auto& S = SProx.Get();

    const Grid& g = D.Grid();
    const Int numObs = D.Height();

    // Compute the average column
    DistMatrix<F> ones(g), xMean(g);
    Ones( ones, numObs, 1 );
    Gemv( TRANSPOSE, F(1)/F(numObs), D, ones, xMean );
    DistMatrix<F,MR,STAR> xMean_MR(g);
    xMean_MR.AlignWith( D );
    xMean_MR = xMean;

    // Subtract the mean from each column of D
    DistMatrix<F> DDev( D );
    for( Int iLoc=0; iLoc<DDev.LocalHeight(); ++iLoc )
        blas::Axpy
        ( DDev.LocalWidth(), F(-1), 
          xMean_MR.LockedBuffer(), 1, 
          DDev.Buffer(iLoc,0),     DDev.LDim() );

    // Form S := 1/(numObs-1) DDev DDev'
    Herk( LOWER, ADJOINT, Base<F>(1)/Base<F>(numObs-1), DDev, S );
    Conjugate( S );
    MakeHermitian( LOWER, S );
}