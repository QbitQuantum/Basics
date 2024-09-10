  void truncatedCG_proj( Vector<Real> &s, Real &snorm, Real &del, int &iflag, int &iter, const Vector<Real> &x,
                         const Vector<Real> &grad, const Real &gnorm, ProjectedObjective<Real> &pObj ) {
    Real tol = std::sqrt(ROL_EPSILON);

    const Real gtol = std::min(tol1_,tol2_*gnorm);

    // Compute Cauchy Point
    Real scnorm = 0.0;
    Teuchos::RCP<Vector<Real> > sc = x.clone();
    cauchypoint(*sc,scnorm,del,iflag,iter,x,grad,gnorm,pObj);
    Teuchos::RCP<Vector<Real> > xc = x.clone();
    xc->set(x);
    xc->plus(*sc);

    // Old and New Step Vectors
    s.set(*sc); 
    snorm = s.norm();
    Real snorm2  = snorm*snorm;
    Teuchos::RCP<Vector<Real> > s1 = x.clone();
    s1->zero();
    Real s1norm2 = 0.0;

    // Gradient Vector
    Teuchos::RCP<Vector<Real> > g = x.clone(); 
    g->set(grad);
    Teuchos::RCP<Vector<Real> > Hs = x.clone();
    pObj.reducedHessVec(*Hs,s,*xc,x,tol);
    g->plus(*Hs);
    Real normg = g->norm();

    // Preconditioned Gradient Vector
    Teuchos::RCP<Vector<Real> > v  = x.clone();
    pObj.reducedPrecond(*v,*g,*xc,x,tol);

    // Basis Vector
    Teuchos::RCP<Vector<Real> > p = x.clone(); 
    p->set(*v); 
    p->scale(-1.0);
    Real pnorm2 = v->dot(*g);

    // Hessian Times Basis Vector
    Teuchos::RCP<Vector<Real> > Hp = x.clone();

    iter        = 0; 
    iflag       = 0; 
    Real kappa  = 0.0;
    Real beta   = 0.0; 
    Real sigma  = 0.0; 
    Real alpha  = 0.0; 
    Real tmp    = 0.0;
    Real gv     = v->dot(*g);
    Real sMp    = 0.0;
    pRed_ = 0.0;

    for (iter = 0; iter < maxit_; iter++) {
      pObj.reducedHessVec(*Hp,*p,*xc,x,tol);

      kappa = p->dot(*Hp);
      if (kappa <= 0) {
        sigma = (-sMp+sqrt(sMp*sMp+pnorm2*(del*del-snorm2)))/pnorm2;
        s.axpy(sigma,*p);
        iflag = 2; 
        break;
      }

      alpha = gv/kappa;
      s1->set(s); 
      s1->axpy(alpha,*p);
      s1norm2 = snorm2 + 2.0*alpha*sMp + alpha*alpha*pnorm2;

      if (s1norm2 >= del*del) {
        sigma = (-sMp+sqrt(sMp*sMp+pnorm2*(del*del-snorm2)))/pnorm2;
        s.axpy(sigma,*p);
        iflag = 3; 
        break;
      }

      pRed_ += 0.5*alpha*gv;

      s.set(*s1);
      snorm2 = s1norm2;  

      g->axpy(alpha,*Hp);
      normg = g->norm();
      if (normg < gtol) {
        break;
      }

      pObj.reducedPrecond(*v,*g,*xc,x,tol);
      tmp   = gv; 
      gv    = v->dot(*g);
      beta  = gv/tmp;    

      p->scale(beta);
      p->axpy(-1.0,*v);
      sMp    = beta*(sMp+alpha*pnorm2);
      pnorm2 = gv + beta*beta*pnorm2; 
    }
    if (iflag > 0) {
      pRed_ += sigma*(gv-0.5*sigma*kappa);
    }

    if (iter == maxit_) {
      iflag = 1;
    }
    if (iflag != 1) { 
      iter++;
    }

    snorm = s.norm();
  }