void MSF_MeasurementBase<EKFState_T>::calculateAndApplyCorrection(
    shared_ptr<EKFState_T> state, MSF_Core<EKFState_T>& core,
    const Eigen::MatrixXd& H_delayed, const Eigen::MatrixXd & res_delayed,
    const Eigen::MatrixXd& R_delayed) {

  // Get measurements.
  /// Correction from EKF update.
  Eigen::Matrix<double, MSF_Core<EKFState_T>::nErrorStatesAtCompileTime, 1> correction_;

  Eigen::MatrixXd S;
  Eigen::MatrixXd K(
      static_cast<int>(MSF_Core<EKFState_T>::nErrorStatesAtCompileTime),
      R_delayed.rows());
  typename MSF_Core<EKFState_T>::ErrorStateCov & P = state->P;

  S = H_delayed * P * H_delayed.transpose() + R_delayed;
  K = P * H_delayed.transpose() * S.inverse();

  correction_ = K * res_delayed;
  const typename MSF_Core<EKFState_T>::ErrorStateCov KH =
      (MSF_Core<EKFState_T>::ErrorStateCov::Identity() - K * H_delayed);
  P = KH * P * KH.transpose() + K * R_delayed * K.transpose();

  // Make sure P stays symmetric.
  P = 0.5 * (P + P.transpose());

  core.applyCorrection(state, correction_);
}