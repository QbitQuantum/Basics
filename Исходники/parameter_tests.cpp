// Combines p-values using Z-score.
double Zscore_combined_pvalue(std::vector<double> &pvals) {

  unsigned long i;
  double z, zcomb, pcomb;

  zcomb = 0.;
  for (i=0; i < pvals.size(); i++) {

    // If some p-value is 0, the score will be 0.
    if (pvals[i] <= 0) {
      return 0;
    }

    // If some p-value is 1, the score will be 1.
    if (pvals[i] >= 1) {
      return 1;
    }

    z = sqrt(2)*boost::math::erf_inv(2*(1-pvals[i]) - 1);       // Sure ???
    zcomb = zcomb + z;
  }
  zcomb = zcomb / sqrt((double) pvals.size());
  pcomb = 1 - 0.5*(1+erf(zcomb/sqrt(2)));
  return pcomb;
}