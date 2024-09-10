 Eigen::Matrix<double,6,1> se3Action(const SE3 & m) const
 { 
   /* X*S = [ R pxR ; 0 R ] [ 0 ; a ] = [ px(Ra) ; Ra ] */
   Eigen::Matrix<double,6,1> res;
   res.tail<3>() = m.rotation() * axis;
   res.head<3>() = m.translation().cross(res.tail<3>());
   return res;
 }