 UncertainTransformation::covariance_t UncertainTransformation::UOplus() const
 {
   Eigen::Matrix<double,6,6> S;
   S.setIdentity();
   S.topRightCorner<3,3>() = -sm::kinematics::crossMx(_t_a_b_a);
   return S.inverse().eval()*_U*S.transpose().inverse().eval();
 }