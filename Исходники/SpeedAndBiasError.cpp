// This evaluates the error term and additionally computes
// the Jacobians in the minimal internal representation.
bool SpeedAndBiasError::EvaluateWithMinimalJacobians(
    double const* const * parameters, double* residuals, double** jacobians,
    double** jacobiansMinimal) const {

  // compute error
  Eigen::Map<const okvis::SpeedAndBias> estimate(parameters[0]);
  okvis::SpeedAndBias error = measurement_ - estimate;

  // weigh it
  Eigen::Map<Eigen::Matrix<double, 9, 1> > weighted_error(residuals);
  weighted_error = squareRootInformation_ * error;

  // compute Jacobian - this is rather trivial in this case...
  if (jacobians != NULL) {
    if (jacobians[0] != NULL) {
      Eigen::Map<Eigen::Matrix<double, 9, 9, Eigen::RowMajor> > J0(
          jacobians[0]);
      J0 = -squareRootInformation_ * Eigen::Matrix<double, 9, 9>::Identity();
    }
  }
  if (jacobiansMinimal != NULL) {
    if (jacobiansMinimal[0] != NULL) {
      Eigen::Map<Eigen::Matrix<double, 9, 9, Eigen::RowMajor> > J0min(
          jacobiansMinimal[0]);
      J0min = -squareRootInformation_ * Eigen::Matrix<double, 9, 9>::Identity();
    }
  }

  return true;
}