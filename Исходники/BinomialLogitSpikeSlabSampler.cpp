  double BLSSS::log_model_prob(const Selector &g) const {
    // borrowed from MLVS.cpp
    double num = spike_->logp(g);
    if (num == BOOM::negative_infinity() || g.nvars() == 0) {
      // If num == -infinity then it is in a zero support point in the
      // prior.  If g.nvars()==0 then all coefficients are zero
      // because of the point mass.  The only entries remaining in the
      // likelihood are sums of squares of y[i] that are independent
      // of g.  They need to be omitted here because they are omitted
      // in the non-empty case below.
      return num;
    }
    SpdMatrix ivar = g.select(slab_->siginv());
    num += .5 * ivar.logdet();
    if (num == BOOM::negative_infinity()) return num;

    Vector mu = g.select(slab_->mu());
    Vector ivar_mu = ivar * mu;
    num -= .5 * mu.dot(ivar_mu);

    bool ok = true;
    ivar += g.select(suf().xtx());
    Matrix L = ivar.chol(ok);
    if (!ok) return BOOM::negative_infinity();
    double denom = sum(log(L.diag()));  // = .5 log |ivar|
    Vector S = g.select(suf().xty()) + ivar_mu;
    Lsolve_inplace(L, S);
    denom -= .5 * S.normsq();  // S.normsq =  beta_tilde ^T V_tilde beta_tilde
    return num - denom;
  }