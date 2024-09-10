void LipmVarHeightPlanner::getAB(const double x0[6], const double u[3], double z0, Eigen::Matrix<double,6,6> &A, Eigen::Matrix<double,6,3> &B) const
{
  A.setIdentity();
  B.setZero();
 
  double x = x0[XX];
  double y = x0[YY];
  double z = x0[ZZ] - z0;

  double px = u[XX];
  double py = u[YY];
  double F = u[ZZ];

  // A
  A(0, 3) = _dt;
  A(1, 4) = _dt;
  A(2, 5) = _dt;

  A(3, 0) = F*_dt/(_mass*z);
  A(3, 2) = F*_dt*(px-x)/(_mass*z*z);

  A(4, 1) = F*_dt/(_mass*z);
  A(4, 2) = F*_dt*(py-y)/(_mass*z*z);
 
  // B
  B(3, 0) = -F*_dt/(_mass*z); 
  B(3, 2) = -(px-x)*_dt/(_mass*z); 
  
  B(4, 1) = -F*_dt/(_mass*z); 
  B(4, 2) = -(py-y)*_dt/(_mass*z);

  B(5, 2) = _dt/_mass; 
}