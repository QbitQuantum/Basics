  /** \brief Compute step.

      Computes a trial step, \f$s_k\f$ as defined by the enum EDescent.  Once the 
      trial step is determined, this function determines an approximate minimizer 
      of the 1D function \f$\phi_k(t) = f(x_k+ts_k)\f$.  This approximate 
      minimizer must satisfy sufficient decrease and curvature conditions.

      @param[out]      s          is the computed trial step
      @param[in]       x          is the current iterate
      @param[in]       obj        is the objective function
      @param[in]       con        are the bound constraints
      @param[in]       algo_state contains the current state of the algorithm
  */
  void compute( Vector<Real> &s, const Vector<Real> &x, Objective<Real> &obj, BoundConstraint<Real> &con, 
                AlgorithmState<Real> &algo_state ) {
    Teuchos::RCP<StepState<Real> > step_state = Step<Real>::getState();

    Real tol = std::sqrt(ROL_EPSILON);

    // Set active set parameter
    Real eps = 0.0;
    if ( con.isActivated() ) {
      eps = algo_state.gnorm;
    }
    lineSearch_->setData(eps);
    if ( hessian_ != Teuchos::null ) {
      hessian_->setData(eps);
    }
    if ( precond_ != Teuchos::null ) {
      precond_->setData(eps);
    }

    // Compute step s
    switch(edesc_) {
      case DESCENT_NEWTONKRYLOV:
        flagKrylov_ = 0;
        krylov_->run(s,*hessian_,*(step_state->gradientVec),*precond_,iterKrylov_,flagKrylov_);
        break;
      case DESCENT_NEWTON:
      case DESCENT_SECANT:
        hessian_->applyInverse(s,*(step_state->gradientVec),tol);
        break;
      case DESCENT_NONLINEARCG:
        nlcg_->run(s,*(step_state->gradientVec),x,obj);
        break;
      case DESCENT_STEEPEST:
        s.set(step_state->gradientVec->dual());
        break;
      default: break;
    }

    // Compute g.dot(s)
    Real gs = 0.0;
    if ( !con.isActivated() ) {
      gs = -s.dot((step_state->gradientVec)->dual());
    }
    else {
      if ( edesc_ == DESCENT_STEEPEST ) {
        d_->set(x);
        d_->axpy(-1.0,s);
        con.project(*d_);
        d_->scale(-1.0);
        d_->plus(x);
        //d->set(s);
        //con.pruneActive(*d,s,x,eps);
        //con.pruneActive(*d,*(step_state->gradientVec),x,eps);
        gs = -d_->dot((step_state->gradientVec)->dual());
      }
      else {
        d_->set(s);
        con.pruneActive(*d_,*(step_state->gradientVec),x,eps);
        gs = -d_->dot((step_state->gradientVec)->dual());
        d_->set(x);
        d_->axpy(-1.0,(step_state->gradientVec)->dual());
        con.project(*d_);
        d_->scale(-1.0);
        d_->plus(x);
        con.pruneInactive(*d_,*(step_state->gradientVec),x,eps);
        gs -= d_->dot((step_state->gradientVec)->dual());
      }
    }

    // Check if s is a descent direction i.e., g.dot(s) < 0
    if ( gs >= 0.0 || (flagKrylov_ == 2 && iterKrylov_ <= 1) ) {
      s.set((step_state->gradientVec)->dual());
      if ( con.isActivated() ) {
        d_->set(s);
        con.pruneActive(*d_,s,x);
        gs = -d_->dot((step_state->gradientVec)->dual());
      }
      else {
        gs = -s.dot((step_state->gradientVec)->dual());
      }
    }
    s.scale(-1.0);

    // Perform line search
    Real fnew  = algo_state.value;
    ls_nfval_ = 0;
    ls_ngrad_ = 0;
    lineSearch_->run(step_state->searchSize,fnew,ls_nfval_,ls_ngrad_,gs,s,x,obj,con);

    // Make correction if maximum function evaluations reached
    if(!acceptLastAlpha_)
    {  
      lineSearch_->setMaxitUpdate(step_state->searchSize,fnew,algo_state.value);
    }

    algo_state.nfval += ls_nfval_;
    algo_state.ngrad += ls_ngrad_;

    // Compute get scaled descent direction
    s.scale(step_state->searchSize);
    if ( con.isActivated() ) {
      s.plus(x);
      con.project(s);
      s.axpy(-1.0,x);
    }

    // Update step state information
    (step_state->descentVec)->set(s);

    // Update algorithm state information
    algo_state.snorm = s.norm();
    algo_state.value = fnew;
  }