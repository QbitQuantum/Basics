void print_Isometry3d(Eigen::Isometry3d pose, std::stringstream &ss){
  Eigen::Vector3d t(pose.translation());
  Eigen::Quaterniond r(pose.rotation());
  ss <<t[0]<<", "<<t[1]<<", "<<t[2]<<" | " 
       <<r.w()<<", "<<r.x()<<", "<<r.y()<<", "<<r.z() ;
  //  std::cout << ss.str() << "q\n";
}