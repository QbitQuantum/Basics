//------------------------------------------------------------------------------
pair<Vector3, Vector3> PreintegrationBase::correctMeasurementsByBiasAndSensorPose(
    const Vector3& j_measuredAcc, const Vector3& j_measuredOmega,
    OptionalJacobian<3, 3> D_correctedAcc_measuredAcc,
    OptionalJacobian<3, 3> D_correctedAcc_measuredOmega,
    OptionalJacobian<3, 3> D_correctedOmega_measuredOmega) const {

  // Correct for bias in the sensor frame
  Vector3 j_correctedAcc = biasHat_.correctAccelerometer(j_measuredAcc);
  Vector3 j_correctedOmega = biasHat_.correctGyroscope(j_measuredOmega);

  // Compensate for sensor-body displacement if needed: we express the quantities
  // (originally in the IMU frame) into the body frame
  // Equations below assume the "body" frame is the CG
  if (p().body_P_sensor) {
    // Correct omega to rotation rate vector in the body frame
    const Matrix3 bRs = p().body_P_sensor->rotation().matrix();
    j_correctedOmega = bRs * j_correctedOmega;

    // Correct acceleration
    j_correctedAcc = bRs * j_correctedAcc;

    // Jacobians
    if (D_correctedAcc_measuredAcc) *D_correctedAcc_measuredAcc = bRs;
    if (D_correctedAcc_measuredOmega) *D_correctedAcc_measuredOmega = Matrix3::Zero();
    if (D_correctedOmega_measuredOmega) *D_correctedOmega_measuredOmega = bRs;

    // Centrifugal acceleration
    const Vector3 b_arm = p().body_P_sensor->translation().vector();
    if (!b_arm.isZero()) {
      // Subtract out the the centripetal acceleration from the measured one
      // to get linear acceleration vector in the body frame:
      const Matrix3 body_Omega_body = skewSymmetric(j_correctedOmega);
      const Vector3 b_velocity_bs = body_Omega_body * b_arm; // magnitude: omega * arm
      j_correctedAcc -= body_Omega_body * b_velocity_bs;
      // Update derivative: centrifugal causes the correlation between acc and omega!!!
      if (D_correctedAcc_measuredOmega) {
        double wdp = j_correctedOmega.dot(b_arm);
        *D_correctedAcc_measuredOmega = -(diag(Vector3::Constant(wdp))
            + j_correctedOmega * b_arm.transpose()) * bRs.matrix()
            + 2 * b_arm * j_measuredOmega.transpose();
      }
    }
  }

  // Do update in one fell swoop
  return make_pair(j_correctedAcc, j_correctedOmega);
}