bool MathUtilities::isRightHandedOrthoNormal( const Vector3s& a, const Vector3s& b, const Vector3s& c, const scalar& tol )
{
  // All basis vectors should be unit
  if( fabs( a.norm() - 1.0 ) > tol ) { return false; }
  if( fabs( b.norm() - 1.0 ) > tol ) { return false; }
  if( fabs( c.norm() - 1.0 ) > tol ) { return false; }
  // All basis vectors should be mutually orthogonal
  if( fabs( a.dot( b ) ) > tol ) { return false; }
  if( fabs( a.dot( c ) ) > tol ) { return false; }
  if( fabs( b.dot( c ) ) > tol ) { return false; }
  // Coordinate system should be right handed
  if( ( a.cross( b ) - c ).lpNorm<Eigen::Infinity>() > tol ) { return false; }
  return true;
}