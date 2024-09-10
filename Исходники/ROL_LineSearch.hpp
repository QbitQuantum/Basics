  virtual bool status( const ELineSearch type, int &ls_neval, int &ls_ngrad, const Real alpha, 
                       const Real fold, const Real sgold, const Real fnew, 
                       const Vector<Real> &x, const Vector<Real> &s, 
                       Objective<Real> &obj, BoundConstraint<Real> &con ) { 
    Real tol = std::sqrt(ROL_EPSILON);

    // Check Armijo Condition
    bool armijo = false;
    if ( con.isActivated() ) {
      Real gs = 0.0;
      if ( edesc_ == DESCENT_STEEPEST ) {
        updateIterate(*d_,x,s,alpha,con);
        d_->scale(-1.0);
        d_->plus(x);
        gs = -s.dot(*d_);
      }
      else {
        d_->set(s);
        d_->scale(-1.0);
        con.pruneActive(*d_,*(grad_),x,eps_);
        gs = alpha*(grad_)->dot(*d_);
        d_->zero();
        updateIterate(*d_,x,s,alpha,con);
        d_->scale(-1.0);
        d_->plus(x);
        con.pruneInactive(*d_,*(grad_),x,eps_);
        gs += d_->dot(grad_->dual());
      }
      if ( fnew <= fold - c1_*gs ) {
        armijo = true;
      }
    }
    else {
      if ( fnew <= fold + c1_*alpha*sgold ) {
        armijo = true;
      }
    }

    // Check Maximum Iteration
    bool itcond = false;
    if ( ls_neval >= maxit_ ) { 
      itcond = true;
    }

    // Check Curvature Condition
    bool curvcond = false;
    if ( armijo && ((type != LINESEARCH_BACKTRACKING && type != LINESEARCH_CUBICINTERP) ||
                    (edesc_ == DESCENT_NONLINEARCG)) ) {
      if (econd_ == CURVATURECONDITION_GOLDSTEIN) {
        if (fnew >= fold + (1.0-c1_)*alpha*sgold) {
          curvcond = true;
        }
      }
      else if (econd_ == CURVATURECONDITION_NULL) {
        curvcond = true;
      }
      else { 
        updateIterate(*xtst_,x,s,alpha,con);
        obj.update(*xtst_);
        obj.gradient(*g_,*xtst_,tol);
        Real sgnew = 0.0;
        if ( con.isActivated() ) {
          d_->set(s);
          d_->scale(-alpha);
          con.pruneActive(*d_,s,x);
          sgnew = -d_->dot(g_->dual());
        }
        else {
          sgnew = s.dot(g_->dual());
        }
        ls_ngrad++;
   
        if (    ((econd_ == CURVATURECONDITION_WOLFE)       
                     && (sgnew >= c2_*sgold))
             || ((econd_ == CURVATURECONDITION_STRONGWOLFE) 
                     && (std::abs(sgnew) <= c2_*std::abs(sgold)))
             || ((econd_ == CURVATURECONDITION_GENERALIZEDWOLFE) 
                     && (c2_*sgold <= sgnew && sgnew <= -c3_*sgold))
             || ((econd_ == CURVATURECONDITION_APPROXIMATEWOLFE) 
                     && (c2_*sgold <= sgnew && sgnew <= (2.0*c1_ - 1.0)*sgold)) ) {
          curvcond = true;
        }
      }
    }

    if (type == LINESEARCH_BACKTRACKING || type == LINESEARCH_CUBICINTERP) {
      if (edesc_ == DESCENT_NONLINEARCG) {
        return ((armijo && curvcond) || itcond);
      }
      else {
        return (armijo || itcond);
      }
    }
    else {
      return ((armijo && curvcond) || itcond);
    }
  }