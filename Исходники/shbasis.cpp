// Perform a linear regression on the power ratio in each order
// Omit l=2 - tends to be abnormally small due to non-isotropic brain-wide fibre distribution
std::pair<float, float> get_regression (const std::vector<float>& ratios)
{
  const size_t n = ratios.size() - 1;
  Eigen::VectorXf Y (n), b (2);
  Eigen::MatrixXf A (n, 2);
  for (size_t i = 1; i != ratios.size(); ++i) {
    Y[i-1] = ratios[i];
    A(i-1,0) = 1.0f;
    A(i-1,1) = (2*i)+2;
  }
  b = (A.transpose() * A).ldlt().solve (A.transpose() * Y);
  return std::make_pair (b[0], b[1]);
}