// Unsigned angle
scalar angleBetweenVectors( const Vector3s& v0, const Vector3s& v1 )
{
  const scalar s = v0.cross( v1 ).norm();
  const scalar c = v0.dot( v1 );
  return atan2( s, c );
}