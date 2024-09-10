 Isometry3d fromSE3Quat(const SE3Quat& t)
 {
   Isometry3d result = (Eigen::Isometry3d) t.rotation();
   result.translation() = t.translation();
   return result;
 }