 Real moment(const size_t m) const {
   if ( m == 1 ) {
     return shape_*scale_;
   }
   if ( m == 2 ) {
     return shape_*scale_*scale_*(1. + shape_);
   }
   return std::pow(scale_,m)*tgamma(shape_+(Real)m)/gamma_shape_; 
 }