void StaticPlaneSphereConstraint::computeGeneralizedFrictionGivenTangentSample( const VectorXs& q, const VectorXs& t, const unsigned column, SparseMatrixsc& D ) const
{
  assert( t.size() == 3 );
  assert( column < unsigned( D.cols() ) );
  assert( q.size() % 12 == 0 );
  assert( fabs( t.norm() - 1.0 ) <= 1.0e-6 );
  assert( fabs( m_plane.n().dot( t ) ) <= 1.0e-6 );

  // Effect on center of mass
  D.insert( 3 * m_sphere_idx + 0, column ) = t.x();
  D.insert( 3 * m_sphere_idx + 1, column ) = t.y();
  D.insert( 3 * m_sphere_idx + 2, column ) = t.z();

  // Effect on orientation
  {
    const unsigned nbodies{ static_cast<unsigned>( q.size() / 12 ) };
    // Compute the displacement from the center of mass to the point of contact
    assert( fabs( m_plane.n().norm() - 1.0 ) <= 1.0e-10 );
    assert( m_r >= 0.0 );
    const Vector3s r_world{ - m_r * m_plane.n() };
    const Vector3s ntilde{ r_world.cross( Eigen::Map<const Vector3s>( t.data() ) ) };
    D.insert( 3 * ( nbodies + m_sphere_idx ) + 0, column ) = ntilde.x();
    D.insert( 3 * ( nbodies + m_sphere_idx ) + 1, column ) = ntilde.y();
    D.insert( 3 * ( nbodies + m_sphere_idx ) + 2, column ) = ntilde.z();
  }
}