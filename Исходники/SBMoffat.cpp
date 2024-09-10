 double SBMoffat::SBMoffatImpl::kV_35(double ksq) const
 {
     double k = sqrt(ksq);
     return exp(-k)*(3.+(3.+k)*k);
 }