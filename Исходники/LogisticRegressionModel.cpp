  double logit_loglike_1(const Vec & beta, bool y, const Vec &x,
			 Vec *g, Mat *h, double mix_wgt){
    double eta = x.dot(beta);
    double lognc = lse2(0, eta);
    double ans = y?  eta : 0;
    ans -= lognc;
    if(g){
      double p = exp(eta-lognc);
      g->axpy(x, mix_wgt* (y-p));
      if(h){
	double q = 1-p;
	h->add_outer( x,x, -mix_wgt * p*q);}}
    return mix_wgt * ans;
  }