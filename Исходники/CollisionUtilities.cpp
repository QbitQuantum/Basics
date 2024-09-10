scalar CollisionUtilities::closestPointSegmentSegment( const Vector3s& p1, const Vector3s& q1, const Vector3s& p2, const Vector3s& q2, scalar& s, scalar& t, Vector3s& c1, Vector3s& c2 )
{
  const scalar DIST_EPS{ 1.0e-8 };

  const Vector3s d1{ q1 - p1 }; // Direction vector of segment S1
  const Vector3s d2{ q2 - p2}; // Direction vector of segment S2
  const Vector3s r{ p1 - p2 };
  const scalar a{ d1.dot( d1 ) }; // Squared length of segment S1, always nonnegative
  const scalar e{ d2.dot( d2 ) }; // Squared length of segment S2, always nonnegative
  const scalar f{ d2.dot( r ) };

  // Check if either or both segments degenerate into points
  if( a <= DIST_EPS && e <= DIST_EPS )
  {
    // Both segments degenerate into points
    s = t = 0.0;
    c1 = p1;
    c2 = p2;
    return ( c1 - c2 ).dot( c1 - c2 );
  }
  if( a <= DIST_EPS )
  {
    // First segment degenerates into a point
    s = 0.0;
    t = f / e; // s = 0 => t = (b*s + f) / e = f / e
    t = clamp( t, 0.0, 1.0 );
  }
  else
  {
    const scalar c{ d1.dot( r ) };
    if( e <= DIST_EPS )
    {
      // Second segment degenerates into a point
      t = 0.0;
      s = clamp( -c / a, 0.0, 1.0 ); // t = 0 => s = (b*t - c) / a = -c / a
    }
    else
    {
      // The general nondegenerate case starts here
      const scalar b{ d1.dot( d2 ) };
      const scalar denom{ a * e - b * b }; // Always nonnegative

      // If segments not parallel, compute closest point on L1 to L2, and
      // clamp to segment S1. Else pick arbitrary s (here 0)
      if( denom != 0.0 )
      {
        s = clamp( ( b * f - c * e ) / denom, 0.0, 1.0 );
      }
      else
      {
        s = 0.0;
      }

      // Compute point on L2 closest to S1(s) using
      // t = Dot((P1+D1*s)-P2,D2) / Dot(D2,D2) = (b*s + f) / e
      t = ( b * s + f ) / e;

      // If t in [0,1] done. Else clamp t, recompute s for the new value
      // of t using s = Dot((P2+D2*t)-P1,D1) / Dot(D1,D1)= (t*b - c) / a
      // and clamp s to [0, 1]
      if( t < 0.0 )
      {
        t = 0.0;
        s = clamp( -c / a, 0.0, 1.0 );
      }
      else if( t > 1.0 )
      {
        t = 1.0;
        s = clamp( (b - c) / a, 0.0, 1.0 );
      }
    }
  }

  c1 = p1 + d1 * s;
  c2 = p2 + d2 * t;
  return ( c1 - c2 ).dot( c1 - c2 );
}