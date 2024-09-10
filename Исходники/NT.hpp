void SUMMA_NTA
( Orientation orientB,
  T alpha,
  const AbstractDistMatrix<T>& APre,
  const AbstractDistMatrix<T>& BPre,
        AbstractDistMatrix<T>& CPre )
{
    EL_DEBUG_CSE
    const Int n = CPre.Width();
    const Int bsize = Blocksize();
    const Grid& g = APre.Grid();
    const bool conjugate = ( orientB == ADJOINT );

    DistMatrixReadProxy<T,T,MC,MR> AProx( APre );
    DistMatrixReadProxy<T,T,MC,MR> BProx( BPre );
    DistMatrixReadWriteProxy<T,T,MC,MR> CProx( CPre );
    auto& A = AProx.GetLocked();
    auto& B = BProx.GetLocked();
    auto& C = CProx.Get();

    // Temporary distributions
    DistMatrix<T,MR,STAR> B1Trans_MR_STAR(g);
    DistMatrix<T,MC,STAR> D1_MC_STAR(g);

    B1Trans_MR_STAR.AlignWith( A );
    D1_MC_STAR.AlignWith( A );

    for( Int k=0; k<n; k+=bsize )
    {
        const Int nb = Min(bsize,n-k);
        auto B1 = B( IR(k,k+nb), ALL        );
        auto C1 = C( ALL,        IR(k,k+nb) );

        // C1[MC,*] := alpha A[MC,MR] (B1^[T/H])[MR,*]
        Transpose( B1, B1Trans_MR_STAR, conjugate );
        LocalGemm( NORMAL, NORMAL, alpha, A, B1Trans_MR_STAR, D1_MC_STAR );

        // C1[MC,MR] += scattered result of D1[MC,*] summed over grid rows
        AxpyContract( T(1), D1_MC_STAR, C1 );
    }
}