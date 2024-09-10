  //----------------------------------------------------------------------
  double LSB::log_model_prob(const Selector &g)const{
    double num = vs_->logp(g);
    if(num==BOOM::negative_infinity()) return num;

    Ominv = g.select(pri_->siginv());
    num += .5*Ominv.logdet();
    if(num == BOOM::negative_infinity()) return num;

    Vec mu = g.select(pri_->mu());
    Vec Ominv_mu = Ominv * mu;
    num -= .5*mu.dot(Ominv_mu);

    bool ok=true;
    iV_tilde_ = Ominv + g.select(suf()->xtx());
    Mat L = iV_tilde_.chol(ok);
    if(!ok)  return BOOM::negative_infinity();
    double denom = sum(log(L.diag()));  // = .5 log |Ominv|

    Vec S = g.select(suf()->xty()) + Ominv_mu;
    Lsolve_inplace(L,S);
    denom-= .5*S.normsq();  // S.normsq =  beta_tilde ^T V_tilde beta_tilde

    return num-denom;
  }