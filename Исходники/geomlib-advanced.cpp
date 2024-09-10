// Determines if 3D triangles intersect.  
// If parallel, returns false. (This may be considered misleading.)
// If true and rpoint is not NULL, returns two edge/triangle intersections.
int Intersects(const Triangle3D& tri1, const Triangle3D& tri2, std::pair<Point3D, Point3D> *rpoints)
{
  // check if coplanar
  if ( abs( ( ( tri1[1] - tri1[0] ) ^ ( tri1[2] - tri1[1] ) ) * ( tri2[1] - tri2[0] ) ) > epsilon )
    return 0;

  std::vector<Point3D> points;

  // test first tri's edges against second tri
  for ( unsigned i = 0; i < 3; ++i )
  {
    unsigned j = ( i == 2 ) ? 0 : i + 1;
    Point3D isect;

    if ( Intersects( Segment3D( tri1[i], tri1[j] ), tri2, &isect ) )
      points.push_back( isect );
  }

  // test second tri's edges against first tri
  for ( unsigned i = 0; i < 3; ++i )
  {
    unsigned j = ( i == 2 ) ? 0 : i + 1;
    Point3D isect;

    if ( Intersects( Segment3D( tri2[i], tri2[j] ), tri1, &isect ) )
      points.push_back( isect );
  }

  if ( rpoints && !points.empty() )
  {
    rpoints->first  = points[0];
    rpoints->second = points[1];
  }

  return points.size();
}