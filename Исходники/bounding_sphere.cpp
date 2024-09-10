void mesh_core::findSphereTouching4Points(
      Eigen::Vector3d& center,
      double& radius,
      const Eigen::Vector3d& a,
      const Eigen::Vector3d& b,
      const Eigen::Vector3d& c,
      const Eigen::Vector3d& d)
{
  Eigen::Matrix3d m;
  m.col(0) = b - a;
  m.col(1) = c - a;
  m.col(2) = d - a;

  double det = m.determinant();

  // points are coplanar?
  if (std::abs(det) <= std::numeric_limits<double>::epsilon())
  {
    findSphereTouching4PointsCoplanar(center, radius, a,b,c,d);
    if (g_verbose)
    {
      logInform("findSphereTouching4Points() COPLANAR  QQQQ");
      logInform("           a = (%7.3f %7.3f %7.3f)",
        a.x(),
        a.y(),
        a.z());
      logInform("           b = (%7.3f %7.3f %7.3f)",
        b.x(),
        b.y(),
        b.z());
      logInform("           c = (%7.3f %7.3f %7.3f)",
        c.x(),
        c.y(),
        c.z());
      logInform("           d = (%7.3f %7.3f %7.3f)",
        d.x(),
        d.y(),
        d.z());
      logInform("           s = (%7.3f %7.3f %7.3f) r=%7.3f",
        center.x(),
        center.y(),
        center.z(),
        radius);
    }
    return;
  }

  double ab_lensq = m.col(0).squaredNorm();
  double ac_lensq = m.col(1).squaredNorm();
  double ad_lensq = m.col(2).squaredNorm();
  Eigen::Vector3d rel_center = ((ad_lensq * m.col(0).cross(m.col(1))) +
                                (ac_lensq * m.col(2).cross(m.col(0))) +
                                (ab_lensq * m.col(1).cross(m.col(2)))) /
                               (2.0 * det);

  radius = rel_center.norm();
  center = rel_center + a;

  if (g_verbose)
  {
    logInform("findSphereTouching4Points()");
    logInform("           a = (%7.3f %7.3f %7.3f)",
      a.x(),
      a.y(),
      a.z());
    logInform("           b = (%7.3f %7.3f %7.3f)",
      b.x(),
      b.y(),
      b.z());
    logInform("           c = (%7.3f %7.3f %7.3f)",
      c.x(),
      c.y(),
      c.z());
    logInform("           d = (%7.3f %7.3f %7.3f)",
      d.x(),
      d.y(),
      d.z());
    logInform("           s = (%7.3f %7.3f %7.3f) r=%7.3f",
      center.x(),
      center.y(),
      center.z(),
      radius);
  }
}