Eigen::Matrix<double, 1, 11> dquatDiffAxisInvar(const Eigen::Vector4d& q1, const Eigen::Vector4d& q2, const Eigen::Vector3d& u)
{
  Vector4d r = quatDiff(q1, q2);
  Matrix<double, 4, 8> dr = dquatDiff(q1, q2);
  Matrix<double, 1, 11> de;
  const auto& rvec = r.tail<3>();
  de << 4.0 * r(0) * dr.row(0) + 4.0 * u.transpose() * rvec *u.transpose() * dr.block<3, 8>(1, 0), 4.0 * u.transpose() * rvec * rvec.transpose();
  return de;
}