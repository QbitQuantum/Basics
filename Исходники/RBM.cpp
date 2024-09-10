Eigen::VectorXd RBM::operator()(const Eigen::VectorXd& x)
{
  v = x.transpose();
  sampleHgivenV();
  return ph.transpose();
}