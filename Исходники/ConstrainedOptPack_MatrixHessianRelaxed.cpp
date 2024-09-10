void MatrixHessianRelaxed::Vp_StPtMtV(
  DVectorSlice* y, value_type a
  , const GenPermMatrixSlice& P, BLAS_Cpp::Transp P_trans
  , BLAS_Cpp::Transp M_trans
  , const SpVectorSlice& x, value_type b ) const
{
  using BLAS_Cpp::no_trans;
  using BLAS_Cpp::trans;
  namespace GPMSIP = AbstractLinAlgPack::GenPermMatrixSliceIteratorPack;
  //
  // y = b*y + a * op(P) * M * x
  // 
  //   = b*y + a * [ op(P1)  op(P2) ] *  [ H   0   ] * [ x1 ]
  //                                     [ 0  bigM ]   [ x2 ]
  //               
  // =>              
  //               
  // y = b*y + a*op(P1)*H*x1 + a*op(P2)*bigM*x2
  //
  LinAlgOpPack::Vp_MtV_assert_sizes(y->size(),P.rows(),P.cols(),P_trans
    , BLAS_Cpp::rows( rows(), cols(), M_trans) );
  LinAlgOpPack::Vp_MtV_assert_sizes( BLAS_Cpp::cols( P.rows(), P.cols(), P_trans)
    ,rows(),cols(),M_trans,x.size());

  // For this to work (as shown below) we need to have P sorted by
  // row if op(P) = P' or sorted by column if op(P) = P.  If
  // P is not sorted properly, we will just use the default
  // implementation of this operation.
  if( 	( P.ordered_by() == GPMSIP::BY_ROW && P_trans == no_trans )
      || 	( P.ordered_by() == GPMSIP::BY_COL && P_trans == trans ) )
  {
    // Call the default implementation
    MatrixOp::Vp_StPtMtV(y,a,P,P_trans,M_trans,x,b);
    return;
  }

  if( P.is_identity() )
    TEUCHOS_TEST_FOR_EXCEPT( !(  BLAS_Cpp::rows( P.rows(), P.cols(), P_trans ) == n_  ) );

  const GenPermMatrixSlice
    P1 = ( P.is_identity() 
         ? GenPermMatrixSlice( n_, n_, GenPermMatrixSlice::IDENTITY_MATRIX )
         : P.create_submatrix(Range1D(1,n_),P_trans==trans?GPMSIP::BY_ROW:GPMSIP::BY_COL)
      ),
    P2 = ( P.is_identity()
         ? GenPermMatrixSlice(
           P_trans == no_trans ? n_ : 1
           , P_trans == no_trans ? 1 : n_
           , GenPermMatrixSlice::ZERO_MATRIX )
         : P.create_submatrix(Range1D(n_+1,n_+1),P_trans==trans?GPMSIP::BY_ROW:GPMSIP::BY_COL)
      );

  const SpVectorSlice
    x1 = x(1,n_);
  const SpVectorSlice::element_type
    *x2_ele = x.lookup_element(n_+1);
  const value_type
    x2 = x2_ele ? x2_ele->value() : 0.0;
  // y = b*y + a*op(P1)*H*x1
  AbstractLinAlgPack::Vp_StPtMtV( y, a, P1, P_trans, *H_, no_trans, x1, b );
  // y += a*op(P2)*bigM*x2
  if( P2.nz() ){
    TEUCHOS_TEST_FOR_EXCEPT( !( P2.nz() == 1 ) );
    const size_type
      i = P_trans == no_trans ? P2.begin()->row_i() : P2.begin()->col_j();
    (*y)(i) += a * bigM_ * x2;
  }
}