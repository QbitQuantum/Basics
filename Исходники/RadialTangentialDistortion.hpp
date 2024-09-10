void RadialTangentialDistortion::undistort(
    const Eigen::MatrixBase<DERIVED> & yconst,
    const Eigen::MatrixBase<DERIVED_JY> & outJy) const {

  EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE_OR_DYNAMIC(
      Eigen::MatrixBase<DERIVED>, 2);
  EIGEN_STATIC_ASSERT_MATRIX_SPECIFIC_SIZE_OR_DYNAMIC(
      Eigen::MatrixBase<DERIVED_JY>, 2, 2);

  Eigen::MatrixBase<DERIVED> & y =
      const_cast<Eigen::MatrixBase<DERIVED> &>(yconst);
  y.derived().resize(2);

  // we use f^-1 ' = ( f'(f^-1) ) '
  // with f^-1 the undistortion
  // and  f the distortion
  undistort(y);  // first get the undistorted image

  Eigen::Vector2d kp = y;
  Eigen::Matrix2d Jd;
  distort(kp, Jd);

  // now y = f^-1(y0)
  DERIVED_JY & J = const_cast<DERIVED_JY &>(outJy.derived());

  J = Jd.inverse();

  /*  std::cout << "J: " << std::endl << J << std::endl;

   double mx2_u = y[0]*y[0];
   double my2_u = y[1]*y[1];
   //double mxy_u = y[0]*y[1];
   double rho2_u = mx2_u+my2_u;

   double rad_dist_u = _k1*rho2_u+_k2*rho2_u*rho2_u;
   // take the inverse as Jacobian.
   J(0,0) = 1/(1 + rad_dist_u + _k1*2*mx2_u + _k2*rho2_u*4*mx2_u + 2*_p1*y[1] + 6*_p2*y[0]);
   J(1,0) = (_k1*2*y[0]*y[1] + _k2*4*rho2_u*y[0]*y[1] + _p1*2*y[0] + 2*_p2*y[1]);
   J(0,1) = J(1,0);
   J(1,1) = 1/(1 + rad_dist_u + _k1*2*my2_u + _k2*rho2_u*4*my2_u + 6*_p1*y[1] + 2*_p2*y[0]);

   // this should only happen if the distortion coefficients are 0
   // the coefficients being zero removes the cross dependence then it is safe to set J(1,0) = 0
   if (J(1,0) != 0)
   J(1,0) = 1/J(1,0);
   J(0,1) = J(1,0);*/

}