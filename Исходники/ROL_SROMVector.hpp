 Real dot( const Vector<Real> &x ) const {
   const SROMVector & ex = Teuchos::dyn_cast<const SROMVector>(x);
   Real pval = pvec_->dot(*(ex.getProbabilityVector()));
   Real aval = avec_->dot(*(ex.getAtomVector()));
   return pval + aval;
 }