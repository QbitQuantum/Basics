inline void
PanelHouseholder( Matrix<F>& A, Matrix<F>& t )
{
#ifndef RELEASE
    CallStackEntry entry("lq::PanelHouseholder");
    if( t.Height() != Min(A.Height(),A.Width()) || t.Width() != 1 )
        LogicError
        ("t must be a vector of height equal to the minimum dimension of A");
#endif
    Matrix<F>
        ATL, ATR,  A00, a01,     A02,  aTopRow, ABottomPan,
        ABL, ABR,  a10, alpha11, a12,
                   A20, a21,     A22;
    Matrix<F>
        tT,  t0,
        tB,  tau1,
             t2;

    Matrix<F> z, aTopRowConj;

    PartitionDownDiagonal
    ( A, ATL, ATR,
         ABL, ABR, 0 );
    PartitionDown
    ( t, tT,
         tB, 0 );
    while( ATL.Height() < A.Height() && ATL.Width() < A.Width() )
    {
        RepartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, /**/ a01,     A02,
         /*************/ /**********************/
               /**/       a10, /**/ alpha11, a12,
          ABL, /**/ ABR,  A20, /**/ a21,     A22, 1 );

        RepartitionDown
        ( tT,  t0,
         /**/ /****/
               tau1,
          tB,  t2, 1 );

        View1x2( aTopRow, alpha11, a12 );
        View1x2( ABottomPan, a21, A22 );
        //--------------------------------------------------------------------//
        // Compute the Householder reflector
        const F tau = Reflector( alpha11, a12 );
        tau1.Set( 0, 0, tau );

        // Apply the Householder reflector
        const F alpha = alpha11.Get(0,0);
        alpha11.Set(0,0,1);
        Conjugate( aTopRow, aTopRowConj );
        Zeros( z, ABottomPan.Height(), 1 );
        Gemv( NORMAL, F(1), ABottomPan, aTopRowConj, F(0), z );
        Ger( -Conj(tau), z, aTopRowConj, ABottomPan );
        alpha11.Set(0,0,alpha);
        //--------------------------------------------------------------------//

        SlidePartitionDown
        ( tT,  t0,
               tau1,
         /**/ /****/
          tB,  t2 );

        SlidePartitionDownDiagonal
        ( ATL, /**/ ATR,  A00, a01,     /**/ A02,
               /**/       a10, alpha11, /**/ a12,
         /*************/ /**********************/
          ABL, /**/ ABR,  A20, a21,     /**/ A22 );
    }
}