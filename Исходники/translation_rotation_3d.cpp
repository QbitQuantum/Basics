void TranslationRotation3D::setF(const std::vector<double> &F_in) {
  if (F_in.size() != 16)
    throw std::runtime_error(
        "TranslationRotation3D::setF: F_in requires 16 elements");

  if ((F_in.at(12) != 0.0) || (F_in.at(13) != 0.0) || (F_in.at(14) != 0.0) ||
      (F_in.at(15) != 1.0))
    throw std::runtime_error(
        "TranslationRotation3D::setF: bottom row of F_in should be [0 0 0 1]");

  Eigen::Map<const Eigen::Matrix<double, 4, 4, Eigen::RowMajor> > F_in_eig(
      F_in.data());

  Eigen::Transform<double, 3, Eigen::Affine> F;
  F = F_in_eig;

  double tmpT[3];
  Eigen::Map<Eigen::Vector3d> tra_eig(tmpT);
  tra_eig = F.translation();

  double tmpR_mat[9];
  Eigen::Map<Eigen::Matrix<double, 3, 3, Eigen::RowMajor> > rot_eig(tmpR_mat);
  rot_eig = F.rotation();

  setT(tmpT);
  setR_mat(tmpR_mat);
  updateR_mat(); // for stability
}