  void GaussianRegGradHessian::computeCovariance(const double& val, const MatrixXd& hessian)
  {
    covariance = hessian.inverse();
//     hessian.computeInverse(&covariance);
    if(data_has_errors==false){covariance *= (val/( (double)(points->size() - npars) ) );}
    else if(errors_are_weights==true)
    {
      double scale = 0.;
      for(unsigned int i=0;i<data_errors->size();i++)
      {
        double temp = 1./((*data_errors)[i]);temp*=temp;
        scale += temp;
      }
      covariance *= val/(scale - (double)npars);
    }
  }