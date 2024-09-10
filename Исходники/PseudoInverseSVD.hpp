// typename DerivedA::Scalar
void pseudo_inverse_svd(const Eigen::MatrixBase<DerivedA>& M,
  Eigen::MatrixBase<OutputMatrixType>& Minv,
  typename DerivedA::Scalar epsilon = 1e-6)//std::numeric_limits<typename DerivedA::Scalar>::epsilon())
{
  // CONTROLIT_INFO << "Method called!\n  epsilon = " << epsilon << ", M = \n" << M;

  // Ensure matrix Minv has the correct size.  Its size should be equal to M.transpose().
  assert_msg(M.rows() == Minv.cols(), "Minv has invalid number of columns.  Expected " << M.rows() << " got " << Minv.cols());
  assert_msg(M.cols() == Minv.rows(), "Minv has invalid number of rows.  Expected " << M.cols() << " got " << Minv.rows());

  // According to Eigen documentation, "If the input matrix has inf or nan coefficients, the result of the
  // computation is undefined, but the computation is guaranteed to terminate in finite (and reasonable) time."
  Eigen::JacobiSVD<DerivedA> svd = M.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV);

  // Get the max singular value
  typename DerivedA::Scalar maxSingularValue = svd.singularValues().array().abs().maxCoeff();

  // Use Minv to temporarily hold sigma
  Minv.setZero();

  typename DerivedA::Scalar tolerance = 0;

  // Only compute sigma if the max singular value is greater than zero.
  if (maxSingularValue > epsilon)
  {
    tolerance = epsilon * std::max(M.cols(), M.rows()) * maxSingularValue;

    // For each singular value of matrix M's SVD decomposition, check if it is greater than
    // the tolerance value.  If it is, save 1/(singular value) in the sigma vector.
    // Otherwise save zero in the sigma vector.
    DerivedA sigmaVector = DerivedA( (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0) );
    // DerivedA zeroSVs = DerivedA( (svd.singularValues().array().abs() <= tolerance).select(svd.singularValues().array().inverse(), 0) );

    // CONTROLIT_INFO << "epsilon: " << epsilon << ", std::max(M.cols(), M.rows()): " << std::max(M.cols(), M.rows()) << ", maxSingularValue: " << maxSingularValue << ", tolerance: " << tolerance;
    // CONTROLIT_INFO << "sigmaVector = " << sigmaVector.transpose();
    // CONTROLIT_INFO << "zeroSigmaVector : "<< zeroSVs.transpose();

    Minv.block(0, 0, sigmaVector.rows(), sigmaVector.rows()) = sigmaVector.asDiagonal();
  }

  // Double check to make sure the matrices have the correct dimensions
  assert_msg(svd.matrixV().cols() == Minv.rows(),
    "Matrix dimension mismatch, svd.matrixV().cols() = " << svd.matrixV().cols() << ", Minv.rows() = " << Minv.rows() << ".");
  assert_msg(Minv.cols() == svd.matrixU().adjoint().rows(),
    "Matrix dimension mismatch, Minv.cols() = " << Minv.cols() << ", svd.matrixU().adjoint().rows() = " << svd.matrixU().adjoint().rows() << ".");

  Minv = svd.matrixV() *
         Minv *
         svd.matrixU().adjoint(); // take the transpose of matrix U

  // CONTROLIT_INFO << "Done method call! Minv = " << Minv;

  // typename DerivedA::Scalar errorNorm = std::abs((M * Minv - DerivedA::Identity(M.rows(), Minv.cols())).norm());

  // if (tolerance != 0 && errorNorm > tolerance * 10)
  // {
  //   CONTROLIT_WARN << "Problems computing pseudoinverse.  Perhaps the tolerance is too high?\n"
  //     << "  - epsilon: " << epsilon << "\n"
  //     << "  - tolerance: " << tolerance << "\n"
  //     << "  - maxSingularValue: " << maxSingularValue << "\n"
  //     << "  - errorNorm: " << errorNorm << "\n"
  //     << "  - M:\n" << M << "\n"
  //     << "  - Minv:\n" << Minv;
  // }

  // return errorNorm;
}