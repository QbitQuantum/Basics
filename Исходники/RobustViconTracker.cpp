double RobustViconTracker::angle_between(const Eigen::Vector3f& v1, const Eigen::Vector3f& v2)
{
  return acos(v1.dot(v2) / (v1.norm() * v2.norm()));
}