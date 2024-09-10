void StapleStapleUtilities::computeStapleHalfPlaneActiveSet( const Vector3s& cm, const Matrix33sr& R, const RigidBodyStaple& staple,
                                                             const Vector3s& x0, const Vector3s& n, std::vector<int>& points )
{
  // For each vertex of the staple
  for( int i = 0; i < 4; ++i )
  {
    const Vector3s v{ R * staple.points()[ i ] + cm };
    // Compute the distance from the vertex to the halfplane
    const scalar d{ n.dot( v - x0 ) - staple.r() };
    // If the distance is not positive, we have a collision!
    if( d <= 0.0 )
    {
      points.emplace_back( i );
    }
  }
}