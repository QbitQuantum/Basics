//==============================================================================
Eigen::Vector6d FreeJoint::getPositionDifferencesStatic(
    const Eigen::Vector6d& _q2,
    const Eigen::Vector6d& _q1) const
{
  const Eigen::Isometry3d T1 = convertToTransform(_q1);
  const Eigen::Isometry3d T2 = convertToTransform(_q2);

  return convertToPositions(T1.inverse() * T2);
}