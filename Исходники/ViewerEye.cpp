 Eigen::Matrix4d ViewerEye::getView() const {
     Eigen::Isometry3d transformedPose = getPoseIsometry();
     return transformedPose.inverse().matrix();
 }