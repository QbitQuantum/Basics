float mmf::OptSO3vMFCF::conjugateGradientCUDA_impl(Matrix3f& R, float res0,
    uint32_t n, uint32_t maxIter) {
  Eigen::Matrix3f N = Eigen::Matrix3f::Zero();
  // tauR_*R^T is the contribution of the motion prior between two
  // frames to regularize solution in case data exists only on certain
  // axes
  if (this->t_ >= 1) N += tauR_*R.transpose();
  for (uint32_t j=0; j<6; ++j) { 
    Eigen::Vector3f m = Eigen::Vector3f::Zero();
    m(j/2) = j%2==0?1.:-1.;
    N += m*this->cld_.xSums().col(j).transpose();
  }
  Eigen::JacobiSVD<Eigen::Matrix3f> svd(N,Eigen::ComputeThinU|Eigen::ComputeThinV);
  if (svd.matrixV().determinant()*svd.matrixU().determinant() > 0)
    R = svd.matrixV()*svd.matrixU().transpose();
  else
    R = svd.matrixV()*Eigen::Vector3f(1.,1.,-1.).asDiagonal()*svd.matrixU().transpose();

//  if (R.determinant() < 0.) {
//    //R *= -1.;
////    R = svd.matrixV()*Eigen::Vector3f(1.,1.,-1.).asDiagonal()*svd.matrixU().transpose();
//    std::cout << "determinant of R < 0" << std::endl;
//  }
//  std::cout << R.determinant() << std::endl;
//  std::cout << "N" << std::endl << N << std::endl;
//  std::cout << "R" << std::endl << R << std::endl;
//  std::cout << this->cld_.xSums() << std::endl;
  return (N*R).trace();
}