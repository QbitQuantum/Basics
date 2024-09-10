void MultiplyAdjoint
( Scalar alpha, const LowRank<Scalar>& A,
                const LowRank<Scalar>& B,
                      LowRank<Scalar>& C )
{
#ifndef RELEASE
    CallStackEntry entry("hmat_tools::MultiplyAdjoint (F := F F^H)");
    if( A.Width() != B.Width() )
        throw std::logic_error("Cannot multiply nonconformal matrices.");
#endif
    const int m = A.Height();
    const int n = B.Height();
    const int Ar = A.Rank();
    const int Br = B.Rank();
    if( Ar <= Br )
    {
        const int r = Ar;
        C.U.SetType( GENERAL ); C.U.Resize( m, r );
        C.V.SetType( GENERAL ); C.V.Resize( n, r );

        // C.U C.V^T = alpha (A.U A.V^T) (B.U B.V^T)^H
        //           = alpha A.U A.V^T conj(B.V) B.U^H
        //           = A.U (alpha conj(B.U) (B.V^H A.V)))^T
        //           = A.U (alpha conj(B.U) W)^T
        //
        // C.U := A.U
        // W := B.V^H A.V
        // C.V := alpha conj(B.U) W
        Copy( A.U, C.U );
        Dense<Scalar> W( Br, Ar ), cBU;
        blas::Gemm
        ( 'C', 'N', Br, Ar, A.Width(),
          1, B.V.LockedBuffer(), B.V.LDim(),
             A.V.LockedBuffer(), A.V.LDim(),
          0, W.Buffer(),         W.LDim() );
        Conjugate( B.U, cBU );
        blas::Gemm
        ( 'N', 'N', n, Ar, Br,
          alpha, cBU.LockedBuffer(), cBU.LDim(),
                 W.LockedBuffer(),   W.LDim(),
          0,     C.V.Buffer(),       C.V.LDim() );
    }
    else // B.r < A.r
    {
        const int r = Br;
        C.U.SetType( GENERAL ); C.U.Resize( m, r );
        C.V.SetType( GENERAL ); C.V.Resize( n, r );

        // C.U C.V^T := alpha (A.U A.V^T) (B.U B.V^T)^H
        //            = alpha A.U A.V^T conj(B.V) B.U^H
        //            = (alpha A.U A.V^T conj(B.U)) conj(B.U)^T
        //            = (alpha A.U W) conj(B.U)^T
        //
        // W := A.V^T conj(B.U)
        // C.U := alpha A.U W
        // C.V := conj(B.U)
        Dense<Scalar> W( Ar, Br ), cBU;
        Conjugate( B.U, cBU );
        blas::Gemm
        ( 'T', 'N', Ar, Br, B.Height(),
          1, A.V.LockedBuffer(), A.V.LDim(),
             cBU.LockedBuffer(), cBU.LDim(),
          0, W.Buffer(),         W.LDim() );
        blas::Gemm
        ( 'N', 'N', A.Height(), Br, Ar,
          alpha, A.U.LockedBuffer(), A.U.LDim(),
                       W.LockedBuffer(),   W.LDim(),
          0,           C.U.Buffer(),       C.U.LDim() );
        Conjugate( B.U, C.V );
    }
}