Eigen::Vector4f IncrementalPlaneEstimator::
getPlane(const Eigen::Vector3d& iSum,
         const Eigen::Matrix3d& iSumSquared,
         const double iCount) {
  Eigen::Vector3d mean = iSum/iCount;
  Eigen::Matrix3d cov = iSumSquared/iCount - mean*mean.transpose();
  Eigen::Vector4d plane;
  plane.head<3>() = cov.jacobiSvd(Eigen::ComputeFullV).matrixV().col(2);
  plane[3] = -plane.head<3>().dot(mean);
  return plane.cast<float>();
}    