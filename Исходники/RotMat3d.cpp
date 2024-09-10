void dRz_dtheta(Matrix3x3 &out, double theta)
{
  out.setZero();

  double s = sin(theta);
  double c = cos(theta);

  out(0,0) = -s; out(0,1) = -c;
  out(1,0) = c; out(1,1) = -s;
}