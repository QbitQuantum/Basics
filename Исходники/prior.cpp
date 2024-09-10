double Prior::sample_alpha(Model* model, const VectorView& y, Rand& rng)
{
  // then use full conditional of alpha to update it
  size_t nterms = (model->beta).length() - m_e;

  double a = alpha_;

  do { // disallow exact zero value
    if (nterms > 0){
      // propose switching sign of alpha and eta (sign of eta has no effect as long
      // as we actually sample beta; note that eta has symmetric zero mean
      // distribution); this is metropolis move with deterministic
      // proposal; no effect is mu_alpha is zero (might as well skip...)
      if ((a <= 0.0) || log(rng.rand_01()) <= -2.0 * mu_alpha * a){
        a = -a;
      }

      Vector xb(n);
      Vector eb(n);

      xb.set_to_product((model->x).columnblock(m_e, nterms),
          (model->beta).block(m_e, nterms), false);
      eb.set_to_product((model->x).columnblock(0, m_e),
          (model->beta).block(0, m_e), false);
      eb -= y; // note: this is E * b - y, hence there is minus below in mu formul.

      double alpha_sigma2 = a * model->sigma2;
      double var = 1.0 / (1.0 + VectorView::dotproduct(xb, xb) / (a * alpha_sigma2));
      double mu = var * (mu_alpha - VectorView::dotproduct(eb, xb) / alpha_sigma2);

      a = sqrt(var) * rng.rand_normal() + mu;
    } else {
      // sample from prior
      a = rng.rand_normal() + mu_alpha;
    }
  } while (a == 0 || a * a == 0);
  model->mu_beta_computed = false;

  return a;
}