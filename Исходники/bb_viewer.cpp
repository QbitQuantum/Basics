Eigen::Affine3f createTransMatrix( float tx, float ty, float tz ) {
  Eigen::Affine3f m = Eigen::Affine3f::Identity();
  m.translation() = Eigen::Vector3f( tx, ty, tz );
  
  return m;
}