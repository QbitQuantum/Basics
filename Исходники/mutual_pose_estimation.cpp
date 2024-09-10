Eigen::Matrix3d MutualPoseEstimation::vrrotvec2mat(double p, Eigen::Vector3d r){
  double s = sin(p);
  double c = cos(p);
  double t = 1 - c;
  r.normalize();
  Eigen::Vector3d n = r;

  double x = n[0];
  double y = n[1];
  double z = n[2];
  Eigen::Matrix3d m(3,3);
  m(0,0) = t*x*x + c; m(0,1) = t*x*y - s*z; m(0,2) = t*x*z + s*y;
  m(1,0) = t*x*y + s*z; m(1,1) = t*y*y + c; m(1,2) = t*y*z - s*x;
  m(2,0) = t*x*z - s*y; m(2,1) = t*y*z + s*x; m(2,2) = t*z*z + c;
  return m;
}