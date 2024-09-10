void ErrorStateKF<Scalar>::predict(const ErrorStateKF<Scalar>::vec3 &wbody,
                                   const ErrorStateKF<Scalar>::mat3 &varW,
                                   const ErrorStateKF<Scalar>::vec3 &abody,
                                   const ErrorStateKF<Scalar>::mat3 &varA, 
                                   Scalar dt) {

  const vec3 ah = abody - ba_; //  corrected inputs
  const vec3 wh = wbody - bg_;
  const mat3 wRb = q_.matrix(); //  current orientation

  //  integrate state forward w/ euler equations
  const quat dq =
      q_ * quat(0, wh[0] * 0.5, wh[1] * 0.5, wh[2] * 0.5);
  q_.w() += dq.w() * dt;
  q_.x() += dq.x() * dt;
  q_.y() += dq.y() * dt;
  q_.z() += dq.z() * dt;
  q_.normalize();
  p_ += v_ * dt;
  v_ += (wRb * ah + vec3(0, 0, -g_)) * dt;

  //  construct error-state jacobian
  mat15 F;
  F.setZero();

  ///  dth = [wh] x dth - bg
  F.template block<3, 3>(0, 0) = -kr::skewSymmetric(wh);
  F.template block<3, 3>(0, 3) = -mat3::Identity();

  //  dv = -R[ah] x dth - R[ba]
  F.template block<3, 3>(6, 0) = -wRb * kr::skewSymmetric(ah);
  F.template block<3, 3>(6, 9) = -wRb;

  //  dp = dv
  F.template block<3, 3>(12, 6).setIdentity();

  //  form process covariance matrix
  Eigen::Matrix<Scalar, 12, 12> Q;
  Q.setZero();
  Q.template block<3, 3>(0, 0) = varW;
  Q.template block<3, 3>(3, 3) = Qbg_;
  Q.template block<3, 3>(6, 6) = varA;
  Q.template block<3, 3>(9, 9) = Qba_;

  Eigen::Matrix<Scalar,15,12> G;
  G.setZero();

  //  angular vel. variance on error state angle
  G.template block<3, 3>(0, 0) = mat3::Identity() * -1;
  G.template block<3, 3>(3, 3).setIdentity();
  G.template block<3, 3>(6, 6) = -wRb; //  acceleration on linear velocity
  G.template block<3, 3>(9, 9).setIdentity();

  //  integrate covariance forward
  P_ += (F * P_ + P_ * F.transpose() + G * Q * G.transpose()) * dt;
}