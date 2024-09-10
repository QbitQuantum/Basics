Matrix3d
getOrientationAndCentriods(Vector3d & p0a,
                           Vector3d & p0b,
                           Vector3d & p0c,
                           Vector3d & p1a,
                           Vector3d & p1b,
                           Vector3d & p1c,
                           Vector3d & c0,
                           Vector3d & c1)
{
  c0 = (p0a+p0b+p0c)*(1.0/3.0);
  c1 = (p1a+p1b+p1c)*(1.0/3.0);

  // subtract out
  p0a -= c0;
  p0b -= c0;
  p0c -= c0;
  p1a -= c1;
  p1b -= c1;
  p1c -= c1;

  Matrix3d H = p1a*p0a.transpose() + p1b*p0b.transpose() +
               p1c*p0c.transpose();

  JacobiSVD<Matrix3d> svd(H, ComputeFullU | ComputeFullV);
  Matrix3d V = svd.matrixV();

  Matrix3d  R;
  R = V * svd.matrixU().transpose();
  double det = R.determinant();

  if (det < 0.0)
  {
    V.col(2) = V.col(2)*-1.0;
    R = V * svd.matrixU().transpose();
  }
  return R;
}