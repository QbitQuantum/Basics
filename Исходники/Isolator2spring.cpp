const Vector&
Isolator2spring::getStressResultant(void)
{

  double Fy;
  if (po < 1.0e-10) {
    // No strength degradation
    Fy = Fyo;
  } else {
    // Strength degradation based on bearing axial load
    double p2 = x0(1)/po;
    if (p2<0) {
      p2 = 0.0;
    }
    Fy = Fyo*(1-exp(-p2));
  }
  
  
  // Material stresses using rate independent plasticity, return mapping algorithm
  
  // Compute trial stress using elastic tangent
  double fb_try = k1*(x0(2)-sP_n);
  double xi_try = fb_try - q_n;
  
  // Yield function
  double Phi_try = fabs(xi_try) - Fy;
  
  double fspr;
  double dfsds;
  double del_gam;
  int sign;
  
  // Elastic step
  if (Phi_try <= 0.0) {
    // Stress and tangent, update plastic deformation and back stress
    fspr = fb_try;
    dfsds = k1;
    sP_n1 = sP_n;
    q_n1 = q_n;
  }
  
  // Plastic step
  else {
    // Consistency parameter
    del_gam = Phi_try/(k1+H);
    
    sign = (xi_try < 0) ? -1 : 1;
    // Return stress to yield surface
    fspr = fb_try - del_gam*k1*sign;
    dfsds = kbo;
    // Update plastic deformation and back stress
    sP_n1 = sP_n + del_gam*sign;
    q_n1 = q_n + del_gam*H*sign;
  }
  
  // Nonlinear equilibrium and kinematic equations; want to find the 
  // zeros of these equations.
  f0(0) = x0(0) - fspr + x0(1)*x0(3);
  f0(1) = x0(0)*h - Pe*h*x0(3) + x0(1)*(x0(2)+h*x0(3));
  f0(2) = x0(1) - kvo*x0(4);
  f0(3) = utpt[0] - x0(2) - h*x0(3);
  f0(4) = -utpt[1] - x0(2)*x0(3) - h/2.0*x0(3)*x0(3) - x0(4);
  
  int iter = 0;
  double normf0 = f0.Norm();
  static Matrix dfinverse(5,5);
  
  // Solve nonlinear equations using Newton's method
  while (normf0 > tol) {
    
    iter += 1;
    
    // Formulate Jacobian of nonlinear equations
    df(0,0) = 1.0;
    df(0,1) = x0(3);
    df(0,2) = -dfsds;
    df(0,3) = x0(1);
    df(0,4) = 0.0;
    
    df(1,0) = h;
    df(1,1) = x0(2) + h*x0(3);
    df(1,2) = x0(1);
    df(1,3) = (x0(1) - Pe)*h;
    df(1,4) = 0.0;
    
    df(2,0) = 0.0;
    df(2,1) = 1.0;
    df(2,2) = 0.0;
    df(2,3) = 0.0;
    df(2,4) = -kvo;
    
    df(3,0) = 0.0;
    df(3,1) = 0.0;
    df(3,2) = -1.0;
    df(3,3) = -h;
    df(3,4) = 0.0;
    
    df(4,0) = 0.0;
    df(4,1) = 0.0;
    df(4,2) = -x0(3);
    df(4,3) = -(x0(2) + h*x0(3));
    df(4,4) = -1.0;
    
    df.Invert(dfinverse);
    // Compute improved estimate of solution x0
    x0 -= dfinverse*f0;
    
    if (po > 1.0e-10) { // Update strength according to axial load
      double p2 = x0(1)/po;
      if (p2<0) {
	p2 = 0.0;
      }
      Fy = Fyo*(1-exp(-p2));
    }
    
    // Apply plasticity theory again, return mapping algorithm 
    fb_try = k1*(x0(2) - sP_n);
    xi_try = fb_try - q_n;
    
    Phi_try = fabs(xi_try) - Fy;
    // Elastic step
    if (Phi_try <= 0.0) {
      fspr = fb_try;
      dfsds = k1;
      sP_n1 = sP_n;
      q_n1 = q_n;
    }
    
    // Plastic step
    else {
      del_gam = Phi_try/(k1+H);
      sign = (xi_try < 0) ? -1 : 1;
      fspr = fb_try - del_gam*k1*sign;
      dfsds = kbo;
      sP_n1 = sP_n + del_gam*sign;
      q_n1 = q_n + del_gam*H*sign;
    }
    
    // Estimate the residual
    f0(0) = x0(0) - fspr + x0(1)*x0(3);
    f0(1) = x0(0)*h - Pe*h*x0(3) + x0(1)*(x0(2)+h*x0(3));
    f0(2) = x0(1) - kvo*x0(4);
    f0(3) = utpt[0] - x0(2) - h*x0(3);
    f0(4) = -utpt[1] - x0(2)*x0(3) - h/2.0*x0(3)*x0(3) - x0(4);
    
    normf0 = f0.Norm();
    
    if (iter > 19) {
      opserr << "WARNING! Iso2spring: Newton iteration failed. Norm Resid: " << normf0  << endln;
      break;
    }
  }
  
  // Compute stiffness matrix by three step process
  double denom = h*dfsds*(Pe - x0(1)) - x0(1)*x0(1);
  static Matrix fkin(3,2);
  fkin(0,0) = 1.0;
  fkin(1,0) = h;
  fkin(2,0) = 0.0;
  fkin(0,1) = -x0(3);
  fkin(1,1) = -(x0(2) + h*x0(3));
  fkin(2,1) = -1.0;
  
  static Matrix feq(3,3);
  feq(0,0) = (Pe-x0(1))*h/denom;
  feq(0,1) = feq(1,0) = x0(1)/denom;
  feq(1,1) = dfsds/denom;
  feq(0,2) = feq(1,2) = feq(2,0) = feq(2,1) = 0.0;
  feq(2,2) = 1.0/kvo;
  
  static Matrix ftot(2,2);
  static Matrix ktot(2,2);
  ftot.Zero();
  ftot.addMatrixTripleProduct(0.0,fkin,feq,1.0);
  ftot.Invert(ktot);
  
  ks(0,0) = ktot(0,0);
  ks(1,0) = ktot(1,0);
  ks(0,1) = ktot(0,1);
  ks(1,1) = ktot(1,1);
  ks(0,2) = ks(1,2) = ks(2,2) = ks(2,1) = ks(2,0) = 0.0;
  
  
  // Compute force vector
  s3(0) = x0(0);
  s3(1) = -x0(1);
  s3(2) = (x0(1)*utpt[0] + x0(0)*h)/2.0;
  return s3;
}