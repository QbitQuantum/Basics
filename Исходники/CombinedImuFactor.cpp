//------------------------------------------------------------------------------
void PreintegratedCombinedMeasurements::integrateMeasurement(
    const Vector3& measuredAcc, const Vector3& measuredOmega, double deltaT) {

  const Matrix3 dRij = deltaXij_.R(); // expensive when quaternion

  // Update preintegrated measurements.
  Matrix3 D_incrR_integratedOmega; // Right jacobian computed at theta_incr
  Matrix9 F_9x9; // overall Jacobian wrt preintegrated measurements (df/dx)
  Matrix93 G1,G2;
  PreintegrationBase::update(measuredAcc, measuredOmega, deltaT,
      &D_incrR_integratedOmega, &F_9x9, &G1, &G2);

  // Update preintegrated measurements covariance: as in [2] we consider a first order propagation that
  // can be seen as a prediction phase in an EKF framework. In this implementation, contrarily to [2] we
  // consider the uncertainty of the bias selection and we keep correlation between biases and preintegrated measurements
  /* ----------------------------------------------------------------------------------------------------------------------- */

  // Single Jacobians to propagate covariance
  Matrix3 H_vel_biasacc = -dRij * deltaT;
  Matrix3 H_angles_biasomega = -D_incrR_integratedOmega * deltaT;

  // overall Jacobian wrt preintegrated measurements (df/dx)
  Eigen::Matrix<double,15,15> F;
  F.setZero();
  F.block<9, 9>(0, 0) = F_9x9;
  F.block<3, 3>(0, 12) = H_angles_biasomega;
  F.block<3, 3>(6, 9) = H_vel_biasacc;
  F.block<6, 6>(9, 9) = I_6x6;

  // first order uncertainty propagation
  // Optimized matrix multiplication   (1/deltaT) * G * measurementCovariance * G.transpose()
  Eigen::Matrix<double,15,15> G_measCov_Gt;
  G_measCov_Gt.setZero(15, 15);

  // BLOCK DIAGONAL TERMS
  D_t_t(&G_measCov_Gt) = deltaT * p().integrationCovariance;
  D_v_v(&G_measCov_Gt) = (1 / deltaT) * (H_vel_biasacc)
      * (p().accelerometerCovariance + p().biasAccOmegaInit.block<3, 3>(0, 0))
      * (H_vel_biasacc.transpose());
  D_R_R(&G_measCov_Gt) = (1 / deltaT) * (H_angles_biasomega)
      * (p().gyroscopeCovariance + p().biasAccOmegaInit.block<3, 3>(3, 3))
      * (H_angles_biasomega.transpose());
  D_a_a(&G_measCov_Gt) = deltaT * p().biasAccCovariance;
  D_g_g(&G_measCov_Gt) = deltaT * p().biasOmegaCovariance;

  // OFF BLOCK DIAGONAL TERMS
  Matrix3 temp = H_vel_biasacc * p().biasAccOmegaInit.block<3, 3>(3, 0)
      * H_angles_biasomega.transpose();
  D_v_R(&G_measCov_Gt) = temp;
  D_R_v(&G_measCov_Gt) = temp.transpose();
  preintMeasCov_ = F * preintMeasCov_ * F.transpose() + G_measCov_Gt;
}