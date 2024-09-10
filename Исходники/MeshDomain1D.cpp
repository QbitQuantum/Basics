void CircleDomain::position_from_length( const double from_here[3],
                                         double length,
                                         double result_point[3],
                                         MsqError& )
{
  Vector3D b = Vector3D(from_here) - mGeom.center();
  Vector3D vy = mGeom.normal() * b;
  Vector3D vx = vy * mGeom.normal();
  double angle = length / mGeom.radius();
  double x = std::cos( angle );
  double y = std::sin( angle );
  vy *= y/vy.length();
  vx *= x/vx.length();
  Vector3D result = vx + vy;
  result *= mGeom.radius();
  result += mGeom.center();
  result.get_coordinates( result_point );
}