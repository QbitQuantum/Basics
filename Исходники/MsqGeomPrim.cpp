bool MsqCircle::three_point( const Vector3D& p1, 
                             const Vector3D& p2, 
                             const Vector3D& p3, 
                             MsqCircle& result )
{
  Vector3D norm = (p1 - p2) * (p3 - p2);
  if (norm.length_squared() < DBL_EPSILON)
    return false;
  
  MsqLine line1( 0.5*(p1+p2), norm * (p1 - p2) );
  MsqLine line2( 0.5*(p2+p3), norm * (p3 - p2) );
  double t_xsect;
  if (!line1.closest( line2, t_xsect ))
    return false;
  
  Vector3D center = line1.point(t_xsect);
  double radius = ((center - p1).length() +
                   (center - p2).length() +
                   (center - p3).length()) / 3.0;
  result = MsqCircle( center, norm, radius );
  return true;
}