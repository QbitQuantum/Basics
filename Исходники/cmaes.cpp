float felli(const std::vector<float>& xx) {
  Eigen::VectorXf x = Eigen::VectorXf::Zero(xx.size());
  for (size_t i = 0; i < xx.size(); ++i)
    x[i] = xx[i];
  Eigen::VectorXf v = Eigen::VectorXf::Zero(x.size());
  for (size_t i = 0; i < v.size(); ++i)
    v[i] = powf(1e6, i / (x.size() - 1.0f));
  return v.dot((x.array() * x.array()).matrix());
}