void RigidBody3DState::setState( const std::vector<Vector3s>& X, const std::vector<Vector3s>& V, const std::vector<scalar>& M, const std::vector<VectorXs>& R, const std::vector<Vector3s>& omega, const std::vector<Vector3s>& I0, const std::vector<bool>& fixed, const std::vector<unsigned>& geom_indices, const std::vector<std::unique_ptr<RigidBodyGeometry>>& geometry )
{
  assert( X.size() == V.size() );
  assert( X.size() == M.size() );
  assert( X.size() == R.size() );
  assert( X.size() == omega.size() );
  assert( X.size() == I0.size() );
  assert( X.size() == fixed.size() );
  assert( X.size() == geom_indices.size() );

  m_nbodies = X.size();

  // Initialize q
  const unsigned nqdofs{ 12 * unsigned( X.size() ) };
  m_q.resize( nqdofs );
  // Load in center of mass positions
  for( std::vector<Vector3s>::size_type body_num = 0; body_num < X.size(); ++body_num )
  {
    m_q.segment<3>( 3 * body_num ) = X[body_num];
  }
  // Load in the orientations
  for( std::vector<VectorXs>::size_type body_num = 0; body_num < R.size(); ++body_num )
  {
    m_q.segment<9>( 3 * m_nbodies + 9 * body_num ) = R[body_num];
    #ifndef NDEBUG
    {
      const Eigen::Map<const Matrix33sr> Rmat{ R[body_num].data() };
      assert( ( Rmat * Rmat.transpose()- Matrix33sr::Identity() ).lpNorm<Eigen::Infinity>() < 1.0e-9 );
      assert( fabs( Rmat.determinant() - 1.0 ) <= 1.0e-9 );
    }
    #endif
  }

  // Initialize v
  const unsigned nvdofs{ 6 * unsigned( omega.size() ) };
  m_v.resize( nvdofs );
  // Load in center mass velocities
  for( std::vector<Vector3s>::size_type body_num = 0; body_num < V.size(); ++body_num )
  {
    m_v.segment<3>( 3 * body_num ) = V[body_num];
  }
  // Load in angular velocities
  for( std::vector<Vector3s>::size_type body_num = 0; body_num < omega.size(); ++body_num )
  {
    m_v.segment<3>( 3 * m_nbodies + 3 * body_num ) = omega[body_num];
  }

  // Load the mass matrices
  if( nvdofs > 0 )
  {
    m_M0 = formBodySpaceMassMatrix( M, I0 );
    m_Minv0 = formBodySpaceInverseMassMatrix( M, I0 );
    m_M = formWorldSpaceMassMatrix( M, I0, R );
    m_Minv = formWorldSpaceInverseMassMatrix( M, I0, R );
  }

  assert( MathUtilities::isIdentity( m_M0 * m_Minv0, 1.0e-9 ) );
  assert( MathUtilities::isIdentity( m_M * m_Minv, 1.0e-9 ) );

  m_fixed = fixed;
  m_geometry_indices = geom_indices;

  // Load the geometry
  Utilities::cloneVector( geometry, m_geometry );
  assert( std::all_of( m_geometry.begin(), m_geometry.end(), []( const std::unique_ptr<RigidBodyGeometry>& geo ) { return geo != nullptr; } ) );
  assert( std::all_of( m_geometry_indices.begin(), m_geometry_indices.end(), [this]( const unsigned idx ) { return idx < m_geometry.size(); } ) );
}