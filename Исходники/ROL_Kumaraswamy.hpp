 Real moment(const size_t m) const {
   Real val = 0., binom = 0., moment = 0.;
   for (size_t i = 0; i < m; i++) {
     moment = exp2_*tgamma(1.+(Real)i/exp1_)*tgamma(exp2_)/tgamma(1.+exp2_+(Real)i/exp1_);
     binom  = (Real)nchoosek(m,i);
     val   += binom*std::pow(a_,m-i)*std::pow(b_-a_,i+1)*moment;
   }    
   return val; 
 }