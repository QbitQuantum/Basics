void _sir_binom_rmeasure (double *y, double *x, double *p, 
			  int *obsindex, int *stateindex, int *parindex, int *covindex,
			  int ncovars, double *covars, double t) {
  double mean, sd;
  double rep;
  mean = CASE*RHO;
  sd = sqrt(CASE*RHO*(1-RHO));
  rep = nearbyint(rnorm(mean,sd));
  REPORTS = (rep > 0) ? rep : 0;
}