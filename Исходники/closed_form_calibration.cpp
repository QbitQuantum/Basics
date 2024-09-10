Eigen::VectorXd ClosedFormCalibration::solveLagrange(const Eigen::Matrix<double,5,5>& M, double lambda)
{
  // A = M * lambda*W (see paper)
  Eigen::Matrix<double,5,5> A;
  A.setZero();
  A(3,3) = A(4,4) = lambda;
  A.noalias() += M;

  // compute the kernel of A by SVD
  Eigen::JacobiSVD< Eigen::Matrix<double,5,5> > svd(A, ComputeFullV);
  Eigen::VectorXd result = svd.matrixV().col(4);
  //for (int i = 0; i < 5; ++i)
  //std::cout << "singular value " << i << " "  << svd.singularValues()(i) << std::endl;
  //std::cout << "kernel base " << result << std::endl;

  // enforce the conditions
  // x_1 > 0
  if (result(0) < 0.)
    result *= -1;
  // x_4^2 + x_5^2 = 1
  double scale = sqrt(pow(result(3), 2) + pow(result(4), 2));
  result /= scale;

  return result;
}