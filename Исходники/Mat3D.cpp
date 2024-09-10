// ************************************************************************
// rot_z
// creates elementary rotation matrix about z
Mat3D rot_z(const double angle)
{
  Mat3D result;
  double sAngle = 0.0;          // sin of angle
  double cAngle = 0.0;          // cos of angle

  // try some popular angles for better precision
  if (angle == PI) cAngle = -1.0;               // s already 0.0
  else if (angle == PI/2) sAngle = 1.0;         // c already 0.0
  else if (angle == 0.0) cAngle = 1.0;
  else
  {
    sAngle = sin(angle);
    cAngle = cos(angle);
  }
  result.mat[0][0] = (scalarT)cAngle;
  result.mat[0][1] = (scalarT)sAngle;
  result.mat[0][2] = 0.0f;
  result.mat[1][0] = (scalarT)-sAngle;
  result.mat[1][1] = (scalarT)cAngle;
  result.mat[1][2] = 0.0f;
  result.mat[2][0] = 0.0f;
  result.mat[2][1] = 0.0f;
  result.mat[2][2] = 1.0f;

  return result;
}