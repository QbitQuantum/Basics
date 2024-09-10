void ConicDomain::evaluate( Mesh::VertexHandle,
                            const Vector3D& point,
                            Vector3D& closest,
                            Vector3D& normal ) const
{
  // translate such that cone point (mPoint) is at origin
  Vector3D pt = point - mPoint;

  // find the plane containing both the input point an the axis
  Vector3D n = mAxis * pt;
  double len = n.length();
  if (len < 1e-12) { 
      // point on axis
      // choose any plane that does't contain the axis
    if (fabs(mAxis[0]) <= fabs(mAxis[1]) && fabs(mAxis[0]) < fabs(mAxis[2]))
      n = mAxis * Vector3D(1,0,0);
    else if (fabs(mAxis[1]) <= fabs(mAxis[2]))
      n = mAxis * Vector3D(0,1,0);
    else
      n = mAxis * Vector3D(0,0,1);
  }
  else  {
    n /= len;
  }
  // Find two points that are the intersection of the plane with the
  // circular cross-section of the cone centered at mPoint
  Vector3D p1 = mRadius * (n * mAxis);
  Vector3D p2 = -p1;
  // Define two lines of intersect between the cone and the plane
  // as the two lines from the apex to each of p1 and p2.
  Vector3D apex = mHeight * mAxis;
  Vector3D v1 = p1 - apex;
  Vector3D v2 = p2 - apex;
  // Find closest point on each line to input position
  double t1 = v1 % (point - apex) / (v1 % v1);
  double t2 = v2 % (point - apex) / (v2 % v2);
  // Select the closest of the two
  p1 = apex + t1*v1;
  p2 = apex + t2*v2;
  double t;
  if ((p1 - point).length_squared() < (p2 - point).length_squared()) {
    normal = v1 * n;
    closest = p1;
    t = t1;
  }
  else {
    normal = v2 * n;
    closest = p2;
    t = t2;
  }
  // If we're below the apex (t > 0), then the normal
  // should be in the same direction as the axis.  Otherwise
  // it should be in the opposite direction.
  if (t * (normal % mAxis) < 0.0)
    normal = -normal;
  // normalize and translate
  normal *= outwardSign / normal.length();
  closest += mPoint;
}