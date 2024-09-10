IGL_INLINE Eigen::Matrix<Scalar, 3, 3> igl::rotation_matrix_from_directions(
  const Eigen::Matrix<Scalar, 3, 1> v0,
  const Eigen::Matrix<Scalar, 3, 1> v1)
{
  Eigen::Matrix<Scalar, 3, 3> rotM;
  const double epsilon=1e-8;
  Scalar dot=v0.normalized().dot(v1.normalized());
  ///control if there is no rotation
  if ((v0-v1).norm()<epsilon)
  {
    rotM = Eigen::Matrix<Scalar, 3, 3>::Identity();
    return rotM;
  }
  if ((v0+v1).norm()<epsilon)
  {
    rotM = -Eigen::Matrix<Scalar, 3, 3>::Identity();
    rotM(0,0) = 1.;
    std::cerr<<"igl::rotation_matrix_from_directions: rotating around x axis by 180o"<<std::endl;
    return rotM;
  }
  ///find the axis of rotation
  Eigen::Matrix<Scalar, 3, 1> axis;
  axis=v0.cross(v1);
  axis.normalize();

  ///construct rotation matrix
  Scalar u=axis(0);
  Scalar v=axis(1);
  Scalar w=axis(2);
  Scalar phi=acos(dot);
  Scalar rcos = cos(phi);
  Scalar rsin = sin(phi);

  rotM(0,0) =      rcos + u*u*(1-rcos);
  rotM(1,0) =  w * rsin + v*u*(1-rcos);
  rotM(2,0) = -v * rsin + w*u*(1-rcos);
  rotM(0,1) = -w * rsin + u*v*(1-rcos);
  rotM(1,1) =      rcos + v*v*(1-rcos);
  rotM(2,1) =  u * rsin + w*v*(1-rcos);
  rotM(0,2) =  v * rsin + u*w*(1-rcos);
  rotM(1,2) = -u * rsin + v*w*(1-rcos);
  rotM(2,2) =      rcos + w*w*(1-rcos);

  return rotM;
}