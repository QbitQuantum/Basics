inline Eigen::Vector3d reflect_from_surface(const Eigen::Vector3d& v,
    const Eigen::Vector3d& surface_norm)
{
  assert(fabs(surface_norm.norm() - 1.0) < 1e-6);
  const double mag = 2.0*v.dot(surface_norm);
  return v - surface_norm * mag;
}