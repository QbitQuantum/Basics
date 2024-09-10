void Model::construct_preference_and_covariance(
    Eigen::VectorXd &Eta, Eigen::MatrixXd &Omega, const Eigen::MatrixXd &C,
    const Eigen::MatrixXd &M, const Eigen::VectorXd &W,
    const Eigen::MatrixXd &S, const Parameter &parameter) {

  Eigen::VectorXd Mu = C * M * W;
  Eta = Mu;

  Eigen::MatrixXd Psi = W.asDiagonal();
  Psi -= (W * W.transpose());

  Eigen::MatrixXd I(n_alternatives, n_alternatives);
  I.setIdentity();
  Eigen::MatrixXd Phi = C * M * Psi * M.transpose() * C.transpose() +
                        parameter.sig2 * C * I * C.transpose();

  Omega = Phi;
  double rt;
  Eigen::MatrixXd Si = I;

  for (int i = 2; i <= parameter.stopping_time; i++) {
    rt = 1.0 / (1 + exp(i - 202.0) / 25); // [Takao] Not sure what this is.
    Si = S * Si;
    Eta += rt * Si * Mu;
    Omega += pow(rt, 2) * Si * Phi * Si.transpose();
  }
}