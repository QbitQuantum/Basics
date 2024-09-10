  bool FilterBase::checkMahalanobisThreshold(const Eigen::VectorXd &innovation,
                                             const Eigen::MatrixXd &invCovariance,
                                             const double nsigmas)
  {
    double sqMahalanobis = innovation.dot(invCovariance * innovation);
    double threshold = nsigmas * nsigmas;

    if (sqMahalanobis >= threshold)
    {
      FB_DEBUG("Innovation mahalanobis distance test failed. Squared Mahalanobis is: " << sqMahalanobis << "\n" <<
               "Threshold is: " << threshold << "\n" <<
               "Innovation is: " << innovation << "\n" <<
               "Innovation covariance is:\n" << invCovariance << "\n");

      return false;
    }

    return true;
  }