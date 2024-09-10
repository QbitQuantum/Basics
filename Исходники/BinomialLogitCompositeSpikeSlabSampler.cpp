  //----------------------------------------------------------------------
  void BLCSSS::rwm_draw_chunk(int chunk){
    clock_t start = clock();
    const Selector &inc(m_->coef().inc());
    int nvars = inc.nvars();
    Vec full_nonzero_beta = m_->beta();   // only nonzero components
    // Compute information matrix for proposal distribution.  For
    // efficiency, also compute the log-posterior of the current beta.
    Vec mu(inc.select(pri_->mu()));
    Spd siginv(inc.select(pri_->siginv()));
    double original_logpost = dmvn(full_nonzero_beta, mu, siginv, 0, true);

    const std::vector<Ptr<BinomialRegressionData> > &data(m_->dat());
    int nobs = data.size();

    int full_chunk_size = compute_chunk_size();
    int chunk_start = chunk * full_chunk_size;
    int elements_remaining = nvars - chunk_start;
    int this_chunk_size = std::min(elements_remaining, full_chunk_size);
    Selector chunk_selector(nvars, false);
    for(int i = chunk_start; i< chunk_start + this_chunk_size; ++i) {
      chunk_selector.add(i);
    }

    Spd proposal_ivar = chunk_selector.select(siginv);

    for(int i = 0; i < nobs; ++i){
      Vec x = inc.select(data[i]->x());
      double eta = x.dot(full_nonzero_beta);
      double prob = plogis(eta);
      double weight = prob * (1-prob);
      VectorView x_chunk(x, chunk_start, this_chunk_size);
      // Only upper triangle is accessed.  Need to reflect at end of loop.
      proposal_ivar.add_outer(x_chunk, weight, false);
      int yi = data[i]->y();
      int ni = data[i]->n();
      original_logpost += dbinom(yi, ni, prob, true);
    }
    proposal_ivar.reflect();
    VectorView beta_chunk(full_nonzero_beta, chunk_start, this_chunk_size);
    if(tdf_ > 0){
      beta_chunk = rmvt_ivar_mt(
          rng(), beta_chunk, proposal_ivar / rwm_variance_scale_factor_, tdf_);
    }else{
      beta_chunk = rmvn_ivar_mt(
          rng(), beta_chunk, proposal_ivar / rwm_variance_scale_factor_);
    }

    double logpost = dmvn(full_nonzero_beta, mu, siginv, 0, true);
    Vec full_beta(inc.expand(full_nonzero_beta));
    logpost += m_->log_likelihood(full_beta, 0, 0, false);
    double log_alpha = logpost - original_logpost;
    double logu = log(runif_mt(rng()));
    ++rwm_chunk_attempts_;
    if(logu < log_alpha){
      m_->set_beta(full_nonzero_beta);
      ++rwm_chunk_successes_;
    }
    clock_t end = clock();
    rwm_chunk_times_ += double(end - start) / CLOCKS_PER_SEC;
  }