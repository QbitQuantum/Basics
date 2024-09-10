//Does the actual calling of Runge Kutta: default precision is TOLERANCE defined in
//def.h
//Returns >0 if there's a problem with the running
int RGE::callRK(double x1, double x2, DoubleVector & v,
		DoubleVector (*derivs)(double, const DoubleVector &), 
		double eps) {
  using std::fabs;
  using std::log;

  double tol;
  if (eps < 0.0) tol = TOLERANCE;
  else if (eps < EPSTOL) tol = EPSTOL;
  else tol = eps;
  // x1 == x2 with high precision
  if (close(fabs(x1), fabs(x2), EPSTOL)) return 0;

  // RGE in terms of natural log of renormalisation scale
  double from = log(fabs(x1));
  double to = log(fabs(x2));

  double guess = (from - to) * 0.1; //first step size
  double hmin = (from - to) * tol * 1.0e-5; 

  int err =
    integrateOdes(v, from, to, tol, guess, hmin, derivs, odeStepper);
  
  setMu(x2);
  return err;
}