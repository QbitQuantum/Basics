// Calculations
bool Line2::intersect(const Segment2& seg) const
{
  Vector2 d = direction();
  Vector2 v = seg.toVector();
  
  Vector2 num = origin()-seg.source();
  real denom  = d.cross(v);
  
  // Check if line segments are parallel
  if (denom == 0.0f)
    return false;
  
  real t = v.cross(num)/denom;                                   
  real s = d.cross(num)/denom;

  // Check if line segments intersect
  if (s < 0.0f || s > 1.0f || t < 0.0f) 
    return false;
    
  return true;
}