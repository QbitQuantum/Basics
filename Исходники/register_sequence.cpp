void m2tq(Eigen::Vector3f& t, Eigen::Quaternionf& q, const Eigen::Matrix4f& m){
  t.x()=m(0,3);
  t.y()=m(1,3);
  t.z()=m(2,3);
  Eigen::Matrix3f R=m.block<3,3>(0,0);
  q=Eigen::Quaternionf(R);
}