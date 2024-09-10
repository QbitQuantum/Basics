  /** \brief Compute value.

      This function returns the Moreau-Yosida penalty value.
      @param[in]          x   is the current iterate.
      @param[in]          tol is a tolerance for inexact Moreau-Yosida penalty computation.
  */
  Real value( const Vector<Real> &x, Real &tol ) {
    Real half = 0.5;
    // Compute objective function value
    fval_ = obj_->value(x,tol);
    nfval_++;
    // Add value of the Moreau-Yosida penalty
    Real fval = fval_;
    if ( con_->isActivated() ) {
      computePenalty(x);
      fval += half*mu_*(l1_->dot(*l1_) + u1_->dot(*u1_));
    }
    return fval;
  }