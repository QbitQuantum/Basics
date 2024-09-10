void tangent_and_bitangent(const Eigen::Vector3d & n_,
    Eigen::Vector3d & t_, Eigen::Vector3d & b_)
{
  double rmin = 0.99;
  double n0 = n_(0), n1 = n_(1), n2 = n_(2);
  if (std::abs(n0) <= rmin) {
    rmin = std::abs(n0);
    t_(0) = 0.0;
    t_(1) = - n2 / std::sqrt(1.0 - std::pow(n0, 2));
    t_(2) =   n1 / std::sqrt(1.0 - std::pow(n0, 2));
  }
  if (std::abs(n1) <= rmin) {
    rmin = std::abs(n1);
    t_(0) =   n2 / std::sqrt(1.0 - std::pow(n1, 2));
    t_(1) =   0.0;
    t_(2) = - n0 / std::sqrt(1.0 - std::pow(n1, 2));
  }
  if (std::abs(n2) <= rmin) {
    rmin = std::abs(n2);
    t_(0) =  n1 / std::sqrt(1.0 - std::pow(n2, 2));
    t_(1) = -n0 / std::sqrt(1.0 - std::pow(n2, 2));
    t_(2) =  0.0;
  }
  b_ = n_.cross(t_);
  // Check that the calculated Frenet-Serret frame is left-handed (levogiro)
  // by checking that the determinant of the matrix whose columns are the normal,
  // tangent and bitangent vectors has determinant 1 (the system is orthonormal!)
  Eigen::Matrix3d M;
  M.col(0) = n_;
  M.col(1) = t_;
  M.col(2) = b_;
  if (boost::math::sign(M.determinant()) != 1) {
    PCMSOLVER_ERROR("Frenet-Serret local frame is not left-handed!", BOOST_CURRENT_FUNCTION);
  }
}