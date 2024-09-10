void CDKF::measurementUpdate(const ros::Time& prev_stamp,
                             const ros::Time& current_stamp,
                             const double image_angular_velocity,
                             const IMUList& imu_rotations,
                             const bool calc_offset) {
  // convert tracked points to measurement
  Eigen::VectorXd real_measurement(kMeasurementSize);
  accessM(real_measurement, MEASURED_TIMESTAMP).array() =
      (current_stamp - zero_timestamp_).toSec();

  accessM(real_measurement, ANGULAR_VELOCITY).array() = image_angular_velocity;

  if (verbose_) {
    ROS_INFO_STREAM("Measured Values: \n" << real_measurement.transpose());
  }

  // create sigma points
  MeasurementSigmaPoints sigma_points(
      state_, cov_, measurement_noise_sd_, CDKF::stateToMeasurementEstimate,
      imu_rotations, zero_timestamp_, calc_offset);

  // get mean and cov
  Eigen::VectorXd predicted_measurement;
  sigma_points.calcEstimatedMean(&predicted_measurement);
  Eigen::MatrixXd innovation;
  sigma_points.calcEstimatedCov(&innovation);

  if (verbose_) {
    ROS_INFO_STREAM("Predicted Measurements: \n"
                    << predicted_measurement.transpose());
  }

  // calc mah distance
  Eigen::VectorXd diff = real_measurement - predicted_measurement;
  double mah_dist = std::sqrt(diff.transpose() * innovation.inverse() * diff);
  if (mah_dist > mah_threshold_) {
    ROS_WARN("Outlier detected, measurement rejected");
    return;
  }

  Eigen::MatrixXd cross_cov;
  sigma_points.calcEstimatedCrossCov(&cross_cov);

  Eigen::MatrixXd gain = cross_cov * innovation.inverse();

  const Eigen::VectorXd state_diff =
      gain * (real_measurement - predicted_measurement);

  state_ += state_diff;

  cov_ -= gain * innovation * gain.transpose();

  if (verbose_) {
    ROS_INFO_STREAM("Updated State: \n" << state_.transpose());
    ROS_INFO_STREAM("Updated Cov: \n" << cov_);
  }

  // guard against precision issues
  constexpr double kMaxTime = 10000.0;
  if (accessS(state_, STATE_TIMESTAMP)[0] > kMaxTime) {
    rezeroTimestamps(current_stamp);
  }
}