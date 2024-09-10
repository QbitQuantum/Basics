  /** \brief Compute value.

      This function returns the augmented Lagrangian value.
      @param[in]          x   is the current iterate.
      @param[in]          tol is a tolerance for inexact augmented Lagrangian computation.
  */
  Real value( const Vector<Real> &x, Real &tol ) {
    // Evaluate constraint if not already done
    if ( !isConEvaluated_ ) {
      con_->value(*c_,x,tol);
      ncval_++;
      isConEvaluated_ = true;
    }
    // Compute objective function value
    fval_ = obj_->value(x,tol);
    // Apply Lagrange multiplier to constraint
    Real cval = lam_->dot(c_->dual());
    // Compute penalty term
    Real pval = c_->dot(*c_);
    // Compute Augmented Lagrangian value
    Real val = 0.0;
    if (flag_) {
      val = (fval_ - cval)/mu_ + 0.5*pval;
    }
    else {
      val = fval_ - cval + 0.5*mu_*pval;
    }
    nfval_++;
    return val;
  }