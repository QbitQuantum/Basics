 bool CaptureStereoSynchronizer::checkNearPose(
   const geometry_msgs::Pose& new_pose)
 {
   Eigen::Affine3d new_affine;
   tf::poseMsgToEigen(new_pose, new_affine);
   for (size_t i = 0; i < poses_.size(); i++) {
     // convert pose into eigen
     Eigen::Affine3d affine;
     tf::poseMsgToEigen(poses_[i], affine);
     // compute difference
     Eigen::Affine3d diff = affine.inverse() * new_affine;
     double positional_difference = diff.translation().norm();
     if (positional_difference < positional_bin_size_) {
       Eigen::AngleAxisd rotational_difference(diff.rotation());
       if (rotational_difference.angle() < rotational_bin_size_) {
         return true;
       }
     }
   }
   return false;
 }