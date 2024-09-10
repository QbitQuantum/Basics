 Real dot( const Vector<Real> &x ) const {
   const Vector_SimOpt<Real> &xs = Teuchos::dyn_cast<const Vector_SimOpt<Real> >(
     Teuchos::dyn_cast<const Vector<Real> >(x));
   return vec1_->dot(*(xs.get_1())) + vec2_->dot(*(xs.get_2()));
 }