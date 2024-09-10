 bool TransitionLimitXYZRPY::check(FootstepState::Ptr from,
                                   FootstepState::Ptr to) const
 {
   // from * trans = to
   const Eigen::Affine3f diff = to->getPose() * from->getPose().inverse();
   const Eigen::Vector3f diff_pos(diff.translation());
   if (std::abs(diff_pos[0]) < x_max_ &&
       std::abs(diff_pos[1]) < y_max_ &&
       std::abs(diff_pos[2]) < z_max_) {
     float roll, pitch, yaw;
     pcl::getEulerAngles(diff, roll, pitch, yaw);
     return (std::abs(roll) < roll_max_ &&
             std::abs(pitch) < pitch_max_ &&
             std::abs(yaw) < yaw_max_);
   }
   else {
     return false;
   }
 }