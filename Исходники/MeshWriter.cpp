void Projection::init(  const Vector3D& n1, const Vector3D& up1 )
{
  MsqError err;
  const Vector3D n = n1/n1.length();
  const Vector3D u = up1/up1.length();
  
  // Rotate for projection
  const Vector3D z( 0., 0., 1. );
  Vector3D r = n * z;
  double angle = r.interior_angle( n, z, err );
  Matrix3D rot1 = rotation( r, angle );
   
  // In-plane rotation for up vector
  Vector3D pu = u - n * (n % u);
  Vector3D y( 0., 1., 0. );
  angle = z.interior_angle( pu, y, err );
  Matrix3D rot2 = rotation( z, angle );
  
  this->myTransform = rot1 * rot2;
}