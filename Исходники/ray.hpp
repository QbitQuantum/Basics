 void derotate(const Eigen::Matrix3d& rot) {
   pos_ = rot.transpose() * pos_; dir_ = rot.transpose() * dir_; }