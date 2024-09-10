Vector3d nd_b(const Sophus::SE3& T_ba, const Vector3d& n_a)
{
  const Vector3d n_b = T_ba.so3() * n_a;
  const double d_b = 1 - T_ba.translation().dot(n_b);
  return n_b / d_b;
}