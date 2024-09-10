  double multivariateGaussianDensity(const Eigen::VectorXd& mean,
                                         const Eigen::MatrixXd& cov,
                                         const Eigen::VectorXd& z)
  {
    Eigen::VectorXd diff = mean - z;

    Eigen::VectorXd exponent = -0.5 * (diff.transpose() * cov.inverse() * diff);

    return pow(2 * M_PI, (double) z.size() / -2.0) * pow(cov.determinant(), -0.5) *
    exp(exponent(0));

  }