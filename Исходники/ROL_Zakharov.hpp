  void gradient( Vector<Real> &g, const Vector<Real> &x, Real &tol ) {

      Real kdotx = x.dot(*k_);
      Real coeff = 0.25*(2.0*kdotx+pow(kdotx,3.0));

      g.set(x);
      g.scale(2.0);
      g.axpy(coeff,*k_);
  }