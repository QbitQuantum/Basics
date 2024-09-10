 double BinnedSumAgreeingIntensities::operator()(const BinnedSpectrum & spec) const
 {
   return operator()(spec, spec);
 }