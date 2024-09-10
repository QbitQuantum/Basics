void UKF::UpdateState(const VectorXd &z, const VectorXd &z_pred, const MatrixXd &S, const MatrixXd &Zsig) {

  int n_z = z_pred.rows();

  // calculate cross correlation
  MatrixXd Tc = MatrixXd(n_x_, n_z);
  Tc.fill(0.0);
  for (int i = 0; i < 2 * n_aug_ + 1; i++) {
    VectorXd z_diff = Zsig.col(i) - z_pred;
    while (z_diff(1) >  M_PI) z_diff(1) -= 2. * M_PI;
    while (z_diff(1) < -M_PI) z_diff(1) += 2. * M_PI;
    VectorXd x_diff = Xsig_pred_.col(i) - x_;
    while (x_diff(3) >  M_PI) x_diff(3) -= 2. * M_PI;
    while (x_diff(3) < -M_PI) x_diff(3) += 2. * M_PI;
    Tc = Tc + weights_(i) * x_diff * z_diff.transpose();
  }

  MatrixXd K = Tc * S.inverse();  // Kalman gain K
  VectorXd z_diff = z - z_pred;

  while (z_diff(1) >  M_PI) z_diff(1) -= 4. * M_PI;
  while (z_diff(1) < -M_PI) z_diff(1) += 4. * M_PI;

  //update
  x_ = x_ + K * z_diff;
  P_ = P_ - K * S * K.transpose();
}