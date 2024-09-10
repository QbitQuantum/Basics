  ErrorTermTransformation::ErrorTermTransformation(aslam::backend::TransformationExpression T, sm::kinematics::Transformation prior, Eigen::Matrix<double,6,6> N, int debug) : 
    _T(T), _prior(prior), _debug(debug)
  {
    // Fill in the inverse covariance.
    setInvR(N.inverse());

    // Tell the super class about the design variables:
    aslam::backend::DesignVariable::set_t dv;
    _T.getDesignVariables(dv);
    setDesignVariablesIterator(dv.begin(), dv.end());
  }