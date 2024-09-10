void TeleportedCircleCircleConstraint::evalH( const VectorXs& q, const MatrixXXsc& basis, MatrixXXsc& H0, MatrixXXsc& H1 ) const
{
  assert( H0.rows() == 2 ); assert( H0.cols() == 3 );
  assert( H1.rows() == 2 ); assert( H1.cols() == 3 );
  assert( ( basis * basis.transpose() - MatrixXXsc::Identity( 2, 2 ) ).lpNorm<Eigen::Infinity>() <= 1.0e-6 );
  assert( fabs( basis.determinant() - 1.0 ) <= 1.0e-6 );

  // Grab the contact normal
  const Vector2s n{ basis.col( 0 ) };
  // Grab the tangent basis
  const Vector2s t{ basis.col( 1 ) };

  // Format for H:
  //   n^T  r x n
  //   t^T  r x t

  H0.block<1,2>(0,0) = n;
  assert( fabs( MathUtilities::cross( m_r0, n ) ) <= 1.0e-6 );
  H0(0,2) = 0.0;

  H0.block<1,2>(1,0) = t;
  H0(1,2) = MathUtilities::cross( m_r0, t );

  H1.block<1,2>(0,0) = n;
  assert( fabs( MathUtilities::cross( m_r1, n ) ) <= 1.0e-6 );
  H1(0,2) = 0.0;

  H1.block<1,2>(1,0) = t;
  H1(1,2) = MathUtilities::cross( m_r1, t );
}