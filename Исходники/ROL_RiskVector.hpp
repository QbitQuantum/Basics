 Real dot( const Vector<Real> &x ) const {
   const RiskVector<Real> &xs = Teuchos::dyn_cast<const RiskVector<Real> >(
     Teuchos::dyn_cast<const Vector<Real> >(x));
   Real xprod = vec_->dot(*(xs.getVector()));
   if (augmented_) {
     for ( uint i = 0; i < nStat_; i++ ) {
       xprod += stat_[i]*xs.getStatistic(i);
     }
   }
   return xprod;
 }