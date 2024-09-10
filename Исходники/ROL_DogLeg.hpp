  void run( Vector<Real> &s, Real &snorm, Real &del, int &iflag, int &iter, const Vector<Real> &x,
            const Vector<Real> &grad, const Real &gnorm, ProjectedObjective<Real> &pObj ) { 
    Real tol = std::sqrt(ROL_EPSILON<Real>());
    // Compute quasi-Newton step
    pObj.reducedInvHessVec(*s_,grad,x,grad,x,tol);
    s_->scale(-1.0);
    Real sNnorm = s_->norm();
    Real gsN    = s_->dot(grad.dual());
    bool negCurv = false;
    if ( gsN >= 0.0 ) {
      negCurv = true;
    }

    if ( negCurv ) {
      cpt_->run(s,snorm,del,iflag,iter,x,grad,gnorm,pObj);
      pRed_ = cpt_->getPredictedReduction();
      iflag = 2;
    }  
    else {
      // Approximately solve trust region subproblem using double dogleg curve
      if (sNnorm <= del) {        // Use the quasi-Newton step
        s.set(*s_); 
        snorm = sNnorm;
        pRed_ = -0.5*gsN;
        iflag = 0;
      }
      else {                      // quasi-Newton step is outside of trust region
        pObj.reducedHessVec(*Hp_,grad.dual(),x,grad,x,tol);
        Real alpha  = 0.0;
        Real beta   = 0.0;
        Real gnorm2 = gnorm*gnorm;
        Real gBg    = grad.dot(*Hp_);
        Real gamma  = gnorm2/gBg;
        if ( gamma*gnorm >= del || gBg <= 0.0 ) {
            alpha = 0.0;
            beta  = del/gnorm;
            s.set(grad.dual()); 
            s.scale(-beta); 
            snorm = del;
            iflag = 2;
        }
        else {
          Real a = sNnorm*sNnorm + 2.0*gamma*gsN + gamma*gamma*gnorm2;
          Real b = -gamma*gsN - gamma*gamma*gnorm2;
          Real c = gamma*gamma*gnorm2 - del*del;
          alpha  = (-b + sqrt(b*b - a*c))/a;
          beta   = gamma*(1.0-alpha);
          s.set(grad.dual());
          s.scale(-beta);
          s.axpy(alpha,*s_);
          snorm = del;
          iflag = 1;
        }
        pRed_ = (alpha*(0.5*alpha-1)*gsN - 0.5*beta*beta*gBg + beta*(1-alpha)*gnorm2);
      }
    }
    TrustRegion<Real>::setPredictedReduction(pRed_);
  }