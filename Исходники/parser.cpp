//==============================================================================
std::string toString(const Eigen::VectorXd& _v)
{
  return boost::lexical_cast<std::string>(_v.transpose());
}