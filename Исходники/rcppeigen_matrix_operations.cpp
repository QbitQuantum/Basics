Eigen::MatrixXd rcppeigen_ftrans(const Eigen::MatrixXd & A) {
  Eigen::MatrixXd m = A.transpose();
  return m;
}