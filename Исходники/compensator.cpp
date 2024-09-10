void Compensator::motion_compensation(sensor_msgs::PointCloud2::Ptr& msg,
                                      const double timestamp_min,
                                      const double timestamp_max,
                                      const Eigen::Affine3d& pose_min_time,
                                      const Eigen::Affine3d& pose_max_time) {
  using std::abs;
  using std::sin;
  using std::acos;

  Eigen::Vector3d translation =
      pose_min_time.translation() - pose_max_time.translation();
  Eigen::Quaterniond q_max(pose_max_time.linear());
  Eigen::Quaterniond q_min(pose_min_time.linear());
  Eigen::Quaterniond q1(q_max.conjugate() * q_min);
  Eigen::Quaterniond q0(Eigen::Quaterniond::Identity());
  q1.normalize();
  translation = q_max.conjugate() * translation;

  int total = msg->width * msg->height;

  double d = q0.dot(q1);
  double abs_d = abs(d);
  double f = 1.0 / (timestamp_max - timestamp_min);

  // Threshold for a "significant" rotation from min_time to max_time:
  // The LiDAR range accuracy is ~2 cm. Over 70 meters range, it means an angle
  // of 0.02 / 70 =
  // 0.0003 rad. So, we consider a rotation "significant" only if the scalar
  // part of quaternion is
  // less than cos(0.0003 / 2) = 1 - 1e-8.
  if (abs_d < 1.0 - 1.0e-8) {
    double theta = acos(abs_d);
    double sin_theta = sin(theta);
    double c1_sign = (d > 0) ? 1 : -1;
    for (int i = 0; i < total; ++i) {
      size_t offset = i * msg->point_step;
      Scalar* x_scalar =
          reinterpret_cast<Scalar*>(&msg->data[offset + x_offset_]);
      if (std::isnan(*x_scalar)) {
        ROS_DEBUG_STREAM("nan point do not need motion compensation");
        continue;
      }
      Scalar* y_scalar =
          reinterpret_cast<Scalar*>(&msg->data[offset + y_offset_]);
      Scalar* z_scalar =
          reinterpret_cast<Scalar*>(&msg->data[offset + z_offset_]);
      Eigen::Vector3d p(*x_scalar, *y_scalar, *z_scalar);

      double tp = 0.0;
      memcpy(&tp, &msg->data[i * msg->point_step + timestamp_offset_],
             timestamp_data_size_);
      double t = (timestamp_max - tp) * f;

      Eigen::Translation3d ti(t * translation);

      double c0 = sin((1 - t) * theta) / sin_theta;
      double c1 = sin(t * theta) / sin_theta * c1_sign;
      Eigen::Quaterniond qi(c0 * q0.coeffs() + c1 * q1.coeffs());

      Eigen::Affine3d trans = ti * qi;
      p = trans * p;
      *x_scalar = p.x();
      *y_scalar = p.y();
      *z_scalar = p.z();
    }
    return;
  }
  // Not a "significant" rotation. Do translation only.
  for (int i = 0; i < total; ++i) {
    Scalar* x_scalar =
        reinterpret_cast<Scalar*>(&msg->data[i * msg->point_step + x_offset_]);
    if (std::isnan(*x_scalar)) {
      ROS_DEBUG_STREAM("nan point do not need motion compensation");
      continue;
    }
    Scalar* y_scalar =
        reinterpret_cast<Scalar*>(&msg->data[i * msg->point_step + y_offset_]);
    Scalar* z_scalar =
        reinterpret_cast<Scalar*>(&msg->data[i * msg->point_step + z_offset_]);
    Eigen::Vector3d p(*x_scalar, *y_scalar, *z_scalar);

    double tp = 0.0;
    memcpy(&tp, &msg->data[i * msg->point_step + timestamp_offset_],
           timestamp_data_size_);
    double t = (timestamp_max - tp) * f;
    Eigen::Translation3d ti(t * translation);

    p = ti * p;
    *x_scalar = p.x();
    *y_scalar = p.y();
    *z_scalar = p.z();
  }
}