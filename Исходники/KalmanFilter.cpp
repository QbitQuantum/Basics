 void KalmanFilter::updateState(double measurement, double variance, const
     Eigen::Matrix<double, 1, 2>& C, const Eigen::Matrix2d& P_k_km1) {
   Eigen::Matrix<double, 2, 1> K_k = P_k_km1 * C.transpose() *
     (C * P_k_km1 * C.transpose() +
     (Eigen::Matrix<double, 1, 1>() << variance).finished()).inverse();
   P_k_k_ = (Eigen::Matrix2d::Identity() - K_k * C) * P_k_km1;
   x_k_ = x_k_ + K_k *
     ((Eigen::Matrix<double, 1, 1>() << measurement).finished() - C * x_k_);
 }