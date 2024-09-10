// Computes the difference vector of all design variables between the linearization point at marginalization and the current guess, on the tangent space (i.e. log(x_bar - x))
Eigen::VectorXd MarginalizationPriorErrorTerm::getDifferenceSinceMarginalization()
{
  Eigen::VectorXd diff = Eigen::VectorXd(_dimensionDesignVariables);
  diff.setZero();
  int index = 0;
  std::vector<Eigen::MatrixXd>::iterator it_marg = _designVariableValuesAtMarginalization.begin();
  std::vector<aslam::backend::DesignVariable*>::iterator it_current = _designVariables.begin();
  for(;it_current != _designVariables.end(); ++it_current, ++it_marg)
  {
	  // retrieve current value (xbar) and value at marginalization(xHat)
      Eigen::MatrixXd xHat = *it_marg;
      //get minimal difference in tangent space
      Eigen::VectorXd diffVector;
      (*it_current)->minimalDifference(xHat, diffVector);
      //int base = index;
      int dim = diffVector.rows();
      diff.segment(index, dim) = diffVector;
      index += dim;
  }
  return diff;
}