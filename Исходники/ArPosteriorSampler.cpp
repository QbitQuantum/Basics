  void ArPosteriorSampler::draw_phi_univariate() {
    int p = model_->phi().size();
    Vec phi = model_->phi();
    if (!model_->check_stationary(phi)) {
      report_error("ArPosteriorSampler::draw_phi_univariate was called with an "
                   "illegal initial value of phi.  That should never happen.");
    }
    const Spd &xtx(model_->suf()->xtx());
    const Vec &xty(model_->suf()->xty());

    for (int i = 0; i < p; ++i) {
      double initial_phi = phi[i];

      double lo = -1;
      double hi = 1;

      // y - xb  y - xb
      //   bt xtx b  - 2 bt xty + yty

      //  bt xtx b = sum_i sum_j beta[i] beta[j] xtx[i, j]
      //           = beta [i]^2 xtx[i,i] + 2 * sum_{j != i} beta[i] xtx[i, j] * beta[j]
      //             - 2 * beta[i] * xty[i];

      // mean is (xty[i] - sum_{j != i}  )
      double ivar = xtx(i, i);
      double mu = (xty[i] - (phi.dot(xtx.col(i)) - phi[i] * xtx(i, i))) / ivar;
      bool ok = false;
      while (!ok) {
        double candidate = rtrun_norm_2_mt(rng(), mu, sqrt(1.0/ivar), lo, hi);
        phi[i] = candidate;
        if (ArModel::check_stationary(phi)) {
          ok = true;
        } else {
          if (candidate > initial_phi) hi = candidate;
          else lo = candidate;
        }
      }
    }
    model_->set_phi(phi);
  }