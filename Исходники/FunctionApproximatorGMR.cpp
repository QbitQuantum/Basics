/** \todo Document FunctionApproximatorGMR::normalPDFDamped
 */
double FunctionApproximatorGMR::normalPDFDamped(const VectorXd& mu, const MatrixXd& covar, const VectorXd& input)
{
  if(covar.determinant() > 0) // It is invertible
  {
    MatrixXd covar_inverse = covar.inverse();

      double output = exp(-0.5*(input-mu).transpose()*covar_inverse*(input-mu));

      // Check that:
      // if output == 0.0
      // return 0.0;

      // For invertible matrices (which covar apparently was), det(A^-1) = 1/det(A)
      // Hence the 1.0/covar_inverse.determinant() below
      //  ( (2\pi)^N*|\Sigma| )^(-1/2)
      output *= pow(pow(2*M_PI,mu.size())/(covar_inverse.determinant()),-0.5);
      return output;
  }
  else
  {
      //cerr << "WARNING: FunctionApproximatorGMR::normalPDFDamped output close to singularity..." << endl;
      return std::numeric_limits<double>::min();
  }
}