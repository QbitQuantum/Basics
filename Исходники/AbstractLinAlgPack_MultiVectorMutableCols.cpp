void MultiVectorMutableCols::Vp_StMtV(
  VectorMutable* y, value_type a, BLAS_Cpp::Transp M_trans
  ,const Vector& x, value_type b
  ) const
{
  using AbstractLinAlgPack::dot;

  // y = b*y
  LinAlgOpPack::Vt_S(y,b);

  if( M_trans == BLAS_Cpp::no_trans ) {
    //
    // y += a*M*x
    //
    // =>
    //
    // y += a * x(1) * M(:,1) + a * x(2) * M(:,2) + ...
    //
    for( size_type j = 1; j <= col_vecs_.size(); ++j )
      LinAlgOpPack::Vp_StV( y, a * x.get_ele(j), *col_vecs_[j-1] );
  }
  else {
    //
    // y += a*M'*x
    //
    // =>
    //
    // y(1) += a M(:,1)*x
    // y(2) += a M(:,2)*x
    // ...
    //
    for( size_type j = 1; j <= col_vecs_.size(); ++j )
      y->set_ele(
        j
        ,y->get_ele(j) + a * dot(*col_vecs_[j-1],x)
        );
  }
}