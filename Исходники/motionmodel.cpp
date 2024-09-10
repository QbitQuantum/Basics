// update the camera state given a new camera pose
void MotionModel::UpdateCameraPose(const cv::Point3d& newPosition, const cv::Vec4d& newOrientation)
{
  // Compute linear velocity
  cv::Vec3d newLinearVelocity( newPosition - position_ );
  // In order to be robust against fast camera movements linear velocity is smoothed over time
  newLinearVelocity = (newLinearVelocity + linearVelocity_) * 0.5;

  // compute rotation between q1 and q2: q2 * qInverse(q1);
  Eigen::Quaterniond newAngularVelocity = cv2eigen( newOrientation ) * orientation_.inverse();

  // In order to be robust against fast camera movements angular velocity is smoothed over time
  newAngularVelocity = newAngularVelocity.slerp(0.5, angularVelocity_);

  newAngularVelocity.normalize();

  // Update the current state variables

  position_ = newPosition;
  orientation_ = cv2eigen( newOrientation );
  linearVelocity_ = newLinearVelocity;
  angularVelocity_ = newAngularVelocity;
}