bool 
collides( const Circle & c, const LineSegment & l)
{
  
  Vector2 posToCenter = c.GetCenter() - l.GetStart();
  Vector2 dirVec      = l.GetEnd()    - l.GetStart();

  float segmentLength = dirVec.Length();
  // direction vector must be unit vector (ie. length = 1) in this case!
  // otherwise we would need another formula for scalar projection.
  dirVec = dirVec / segmentLength; 

  // scalar projection of posToCenter to direction vector.
  float d = dirVec.Dot(posToCenter);

  // if d value exceeds original segment length, then we put a cap on it.
  // if these two lines are dismissed, then algorithm sees line segment 
  // as a infinite line.
  if ( d >  segmentLength ) d = segmentLength;
  if ( d < -segmentLength ) d = -segmentLength;
  
  // compute closest point to circle center from line start 
  // along direction vector.
  Vector2 closest_point =l.GetStart() + dirVec * d;

  // vectorfrom circle center to closest point on line
  Vector2 S = closest_point - c.GetCenter();

  return (S.Length() <= c.GetRadius());
}