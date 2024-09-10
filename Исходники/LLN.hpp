inline void
TrmmLLNCOld
( UnitOrNonUnit diag,
  T alpha, const DistMatrix<T>& L,
                 DistMatrix<T>& X )
{
#ifndef RELEASE
    CallStackEntry entry("internal::TrmmLLNCOld");
    if( L.Grid() != X.Grid() )
        throw std::logic_error
        ("L and X must be distributed over the same grid");
    if( L.Height() != L.Width() || L.Width() != X.Height() )
    {
        std::ostringstream msg;
        msg << "Nonconformal TrmmLLNC: \n"
            << "  L ~ " << L.Height() << " x " << L.Width() << "\n"
            << "  X ~ " << X.Height() << " x " << X.Width() << "\n";
        throw std::logic_error( msg.str().c_str() );
    }
#endif
    const Grid& g = L.Grid();

    // Matrix views
    DistMatrix<T> 
        LTL(g), LTR(g),  L00(g), L01(g), L02(g),
        LBL(g), LBR(g),  L10(g), L11(g), L12(g),
                         L20(g), L21(g), L22(g);
    DistMatrix<T> XT(g),  X0(g),
                  XB(g),  X1(g),
                          X2(g);

    // Temporary distributions
    DistMatrix<T,STAR,MC  > L10_STAR_MC(g);
    DistMatrix<T,STAR,STAR> L11_STAR_STAR(g);
    DistMatrix<T,STAR,VR  > X1_STAR_VR(g);
    DistMatrix<T,MR,  STAR> D1Trans_MR_STAR(g);
    DistMatrix<T,MR,  MC  > D1Trans_MR_MC(g);
    DistMatrix<T,MC,  MR  > D1(g);

    // Start the algorithm
    Scale( alpha, X );
    LockedPartitionUpDiagonal
    ( L, LTL, LTR,
         LBL, LBR, 0 );
    PartitionUp
    ( X, XT,
         XB, 0 );
    while( XT.Height() > 0 )
    {
        LockedRepartitionUpDiagonal
        ( LTL, /**/ LTR,  L00, L01, /**/ L02,
               /**/       L10, L11, /**/ L12,
         /*************/ /******************/
          LBL, /**/ LBR,  L20, L21, /**/ L22 );

        RepartitionUp
        ( XT,  X0,
               X1,
         /**/ /**/
          XB,  X2 );

        L10_STAR_MC.AlignWith( X0 );
        D1Trans_MR_STAR.AlignWith( X1 );
        D1Trans_MR_MC.AlignWith( X1 );
        D1.AlignWith( X1 );
        //--------------------------------------------------------------------//
        L11_STAR_STAR = L11;
        X1_STAR_VR = X1;
        LocalTrmm( LEFT, LOWER, NORMAL, diag, T(1), L11_STAR_STAR, X1_STAR_VR );
        X1 = X1_STAR_VR;

        L10_STAR_MC = L10;
        LocalGemm
        ( TRANSPOSE, TRANSPOSE, T(1), X0, L10_STAR_MC, D1Trans_MR_STAR );
        D1Trans_MR_MC.SumScatterFrom( D1Trans_MR_STAR );
        Zeros( D1, X1.Height(), X1.Width() );
        Transpose( D1Trans_MR_MC.Matrix(), D1.Matrix() );
        Axpy( T(1), D1, X1 );
        //--------------------------------------------------------------------//
        D1.FreeAlignments();
        D1Trans_MR_MC.FreeAlignments();
        D1Trans_MR_STAR.FreeAlignments();
        L10_STAR_MC.FreeAlignments();

        SlideLockedPartitionUpDiagonal
        ( LTL, /**/ LTR,  L00, /**/ L01, L02,
         /*************/ /******************/
               /**/       L10, /**/ L11, L12, 
          LBL, /**/ LBR,  L20, /**/ L21, L22 );

        SlidePartitionUp
        ( XT,  X0,
         /**/ /**/
               X1,
          XB,  X2 );
    }
}