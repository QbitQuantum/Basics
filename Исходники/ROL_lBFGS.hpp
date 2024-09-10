  // Apply lBFGS Approximate Inverse Hessian
  void applyH( Vector<Real> &Hv, const Vector<Real> &v ) const {
    // Get Generic Secant State
    const Teuchos::RCP<SecantState<Real> >& state = Secant<Real>::get_state();
    Real zero(0);

    Hv.set(v.dual());
    std::vector<Real> alpha(state->current+1,zero);
    for (int i = state->current; i>=0; i--) {
      alpha[i]  = state->iterDiff[i]->dot(Hv);
      alpha[i] /= state->product[i];
      Hv.axpy(-alpha[i],(state->gradDiff[i])->dual());
    }

    // Apply initial inverse Hessian approximation to v
    Teuchos::RCP<Vector<Real> > tmp = Hv.clone();
    Secant<Real>::applyH0(*tmp,Hv.dual());
    Hv.set(*tmp);

    Real beta(0);
    for (int i = 0; i <= state->current; i++) {
      beta  = Hv.dot((state->gradDiff[i])->dual());
      beta /= state->product[i];
      Hv.axpy((alpha[i]-beta),*(state->iterDiff[i]));
    }
  }