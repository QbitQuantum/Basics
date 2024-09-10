/////////////////////////////////////////////////////////////////////////////
// Compute the likelihood of superiority
// This function assumes that the covariance matrix and ratings are computed
/////////////////////////////////////////////////////////////////////////////
void CBradleyTerry::ComputeLikelihoodOfSuperiority() {
  mLOS.SetSize(crs.GetPlayers(), crs.GetPlayers());

  for (int i = mLOS.GetRows(); --i > 0;)
    for (int j = i; --j >= 0;) {
      double Sigma2 = mCovariance.GetElement(i, i) +
          mCovariance.GetElement(j, j) -
          mCovariance.GetElement(i, j) -
          mCovariance.GetElement(j, i);
      double Mu = velo[j] - velo[i];
      double x = Mu / std::sqrt(2 * Sigma2);
      mLOS.SetElement(i, j, erfc(x) / 2);
      mLOS.SetElement(j, i, erfc(-x) / 2);
    }

  for (int i = mLOS.GetRows(); --i >= 0;)
    mLOS.SetElement(i, i, 0.0);
}