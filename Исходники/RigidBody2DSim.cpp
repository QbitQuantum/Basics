void RigidBody2DSim::computeContactBases( const VectorXs& q, const VectorXs& v, const std::vector<std::unique_ptr<Constraint>>& active_set, MatrixXXsc& contact_bases ) const
{
  const unsigned ncols{ static_cast<unsigned>( active_set.size() ) };
  contact_bases.resize( 2, 2 * ncols );
  for( unsigned col_num = 0; col_num < ncols; ++col_num )
  {
    MatrixXXsc basis;
    active_set[col_num]->computeBasis( q, v, basis );
    assert( basis.rows() == basis.cols() ); assert( basis.rows() == 2 );
    assert( ( basis * basis.transpose() - MatrixXXsc::Identity( 2, 2 ) ).lpNorm<Eigen::Infinity>() <= 1.0e-6 );
    assert( fabs( basis.determinant() - 1.0 ) <= 1.0e-6 );
    contact_bases.block<2,2>( 0, 2 * col_num ) = basis;
  }
}