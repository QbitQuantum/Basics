void KalmanFilter::delta_change(){
  
  float dt2_2 = (pow(delta_t_,2))/2;
  
  //Recompute A, state transition
  A_ = Eigen::Matrix<float, 9, 9>::Identity();
  A_ << 1., 0.,   0.,     delta_t_,   0.,     0.,    dt2_2,     0.,     0.,
	0., 1.,   0.,       0.,     delta_t_, 0.,      0.,     dt2_2,   0.,
	0., 0.,   1.,       0.,       0.,   delta_t_,  0.,      0.,    dt2_2,
	0., 0.,   0.,       1.,       0.,     0.,    delta_t_,  0.,     0.,
	0., 0.,   0.,       0.,       1.,     0.,      0.,    delta_t_, 0.,
	0., 0.,   0.,       0.,       0.,     1.,      0.,      0.,     delta_t_,
	0., 0.,   0.,       0.,       0.,     0.,      1.,      0.,     0.,
	0., 0.,   0.,       0.,       0.,     0.,      0.,      1.,     0.,
	0., 0.,   0.,       0.,       0.,     0.,      0.,      0.,     1.;
     
  //Recompute Q, covariance process noise
  Eigen::Matrix<float, 9, 3>  G;
  G.fill(0.);
  //Process noise only in the highest order term
  G(6,0) = delta_t_;
  G(7,1) = delta_t_;
  G(8,2) = delta_t_;
  Q_ = G * sigma_jerk_ * G.transpose();
  
}