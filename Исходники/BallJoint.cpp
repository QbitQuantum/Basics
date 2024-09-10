//==============================================================================
Eigen::Vector3d BallJoint::getPositionDifferencesStatic(
    const Eigen::Vector3d& _q2, const Eigen::Vector3d& _q1) const
{
  const Eigen::Matrix3d R1 = convertToRotation(_q1);
  const Eigen::Matrix3d R2 = convertToRotation(_q2);

  return convertToPositions(R1.transpose() * R2);
}