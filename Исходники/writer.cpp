urdf::Pose transformToPose(const sva::PTransformd& X)
{
  urdf::Pose pose;
  pose.position = fromEigen(X.translation());
  pose.rotation = fromEigen(Eigen::Matrix3d(X.rotation().inverse()));
  return pose;
}