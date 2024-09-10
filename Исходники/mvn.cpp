 //======================================================================
 Vector &impute_mvn(Vector &observation,
                    const Vector &mean, const SpdMatrix &variance,
                    const Selector &observed, RNG &rng) {
   if (observed.nvars() == observed.nvars_possible()) {
     return observation;
   } else if (observed.nvars() == 0) {
     observation = rmvn_mt(rng, mean, variance);
     return observation;
   }
   if (observation.size() != observed.nvars_possible()) {
     report_error("observation and observed must be the same size.");
   }
   
   // The distribution we want is N(mu, V), with 
   //  V = Sig11 - Sig12 Sig22.inv Sig.21
   // and
   // mu = mu1 - Sig12 Sig22.inv (y2 - mu2)
   // The 1's are missing, and the 2's are observed.
   Selector missing = observed.complement();
   Matrix cross_covariance = missing.select_rows(
       observed.select_cols(variance));
   SpdMatrix observed_precision = observed.select_square(variance).inv();
   Vector mu = missing.select(mean) + cross_covariance * observed_precision
       * (observed.select(observation) - observed.select(mean));
   SpdMatrix V = missing.select_square(variance)
       - sandwich(cross_covariance, observed_precision);
   Vector imputed = rmvn_mt(rng, mu, V);
   observed.fill_missing_elements(observation, imputed);
   return observation;
 }