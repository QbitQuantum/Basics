bool GimbalCalibResidual::operator()(const T *const tau_s,
                                     const T *const tau_d,
                                     const T *const w1,
                                     const T *const w2,
                                     const T *const Lambda1,
                                     const T *const Lambda2,
                                     T *residual) const {
  // clang-format off
  // Form the transform from static camera to dynamic camera
  const Eigen::Matrix<T, 4, 4> T_ds = this->T_ds(tau_s, tau_d, w1, w2, Lambda1, Lambda2);

  // Calculate reprojection error by projecting 3D world point observed in
  // dynamic camera to static camera
  // -- Transform 3D world point from dynamic to static camera
  const Eigen::Matrix<T, 3, 1> P_d{T(this->P_d[0]), T(this->P_d[1]), T(this->P_d[2])};
  const Eigen::Matrix<T, 3, 1> P_s_cal = (T_ds.inverse() * P_d.homogeneous()).head(3);
  // -- Project 3D world point to image plane
  const Eigen::Matrix<T, 3, 3> K_s = this->K(T(this->fx_s), T(this->fy_s), T(this->cx_s), T(this->cy_s));
  // const Eigen::Matrix<T, 4, 1> D_s = this->D(T(this->k1_s), T(this->k2_s), T(this->k3_s), T(this->k4_s));
  // const Eigen::Matrix<T, 2, 1> Q_s_cal = this->project_pinhole_equi(K_s, D_s, P_s_cal);
  const Eigen::Matrix<T, 2, 1> Q_s_cal = this->project_pinhole(K_s, P_s_cal);
  // -- Calculate reprojection error
  residual[0] = T(this->Q_s[0]) - Q_s_cal(0);
  residual[1] = T(this->Q_s[1]) - Q_s_cal(1);

  // Calculate reprojection error by projecting 3D world point observed in
  // static camera to dynamic camera
  // -- Transform 3D world point from static to dynamic camera
  const Eigen::Matrix<T, 3, 1> P_s{T(this->P_s[0]), T(this->P_s[1]), T(this->P_s[2])};
  const Eigen::Matrix<T, 3, 1> P_d_cal = (T_ds * P_s.homogeneous()).head(3);
  // -- Project 3D world point to image plane
  const Eigen::Matrix<T, 3, 3> K_d = this->K(T(this->fx_d), T(this->fy_d), T(this->cx_d), T(this->cy_d));
  // const Eigen::Matrix<T, 4, 1> D_d = this->D(T(this->k1_d), T(this->k2_d), T(this->k3_d), T(this->k4_d));
  // const Eigen::Matrix<T, 2, 1> Q_d_cal = this->project_pinhole_equi(K_d, D_d, P_d_cal);
  const Eigen::Matrix<T, 2, 1> Q_d_cal = this->project_pinhole(K_d, P_d_cal);
  // -- Calculate reprojection error
  residual[2] = T(this->Q_d[0]) - Q_d_cal(0);
  residual[3] = T(this->Q_d[1]) - Q_d_cal(1);

  return true;
  // clang-format on
}