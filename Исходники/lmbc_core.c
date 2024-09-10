static void
LNSRCH(int m, LM_REAL *x, LM_REAL f, LM_REAL *g, LM_REAL *p, LM_REAL alpha, LM_REAL *xpls,
       LM_REAL *ffpls, void (*func)(LM_REAL *p, LM_REAL *hx, int m, int n, void *adata), struct FUNC_STATE state,
       int *mxtake, int *iretcd, LM_REAL stepmx, LM_REAL steptl, LM_REAL *sx)
{
/* Find a next newton iterate by backtracking line search.
 * Specifically, finds a \lambda such that for a fixed alpha<0.5 (usually 1e-4),
 * f(x + \lambda*p) <= f(x) + alpha * \lambda * g^T*p
 *
 * Translated (with minor changes) from Schnabel, Koontz & Weiss uncmin.f,  v1.3

 * PARAMETERS :

 *	m       --> dimension of problem (i.e. number of variables)
 *	x(m)    --> old iterate:	x[k-1]
 *	f       --> function value at old iterate, f(x)
 *	g(m)    --> gradient at old iterate, g(x), or approximate
 *	p(m)    --> non-zero newton step
 *	alpha   --> fixed constant < 0.5 for line search (see above)
 *	xpls(m) <--	 new iterate x[k]
 *	ffpls   <--	 function value at new iterate, f(xpls)
 *	func    --> name of subroutine to evaluate function
 *	state   <--> information other than x and m that func requires.
 *			    state is not modified in xlnsrch (but can be modified by func).
 *	iretcd  <--	 return code
 *	mxtake  <--	 boolean flag indicating step of maximum length used
 *	stepmx  --> maximum allowable step size
 *	steptl  --> relative step size at which successive iterates
 *			    considered close enough to terminate algorithm
 *	sx(m)	  --> diagonal scaling matrix for x, can be NULL

 *	internal variables

 *	sln		 newton length
 *	rln		 relative length of newton step
*/

    register int i;
    int firstback = 1;
    LM_REAL disc;
    LM_REAL a3, b;
    LM_REAL t1, t2, t3, lambda, tlmbda, rmnlmb;
    LM_REAL scl, rln, sln, slp;
    LM_REAL tmp1, tmp2;
    LM_REAL fpls, pfpls = 0., plmbda = 0.; /* -Wall */

    f*=CNST(0.5);
    *mxtake = 0;
    *iretcd = 2;
    tmp1 = 0.;
    if(!sx) /* no scaling */
      for (i = 0; i < m; ++i)
        tmp1 += p[i] * p[i];
    else
      for (i = 0; i < m; ++i)
        tmp1 += sx[i] * sx[i] * p[i] * p[i];
    sln = (LM_REAL)sqrt(tmp1);
    if (sln > stepmx) {
	  /*	newton step longer than maximum allowed */
	    scl = stepmx / sln;
      for(i=0; i<m; ++i) /* p * scl */
        p[i]*=scl;
	    sln = stepmx;
    }
    for(i=0, slp=0.; i<m; ++i) /* g^T * p */
      slp+=g[i]*p[i];
    rln = 0.;
    if(!sx) /* no scaling */
      for (i = 0; i < m; ++i) {
	      tmp1 = (FABS(x[i])>=CNST(1.))? FABS(x[i]) : CNST(1.);
	      tmp2 = FABS(p[i])/tmp1;
	      if(rln < tmp2) rln = tmp2;
      }
    else
      for (i = 0; i < m; ++i) {
	      tmp1 = (FABS(x[i])>=CNST(1.)/sx[i])? FABS(x[i]) : CNST(1.)/sx[i];
	      tmp2 = FABS(p[i])/tmp1;
	      if(rln < tmp2) rln = tmp2;
      }
    rmnlmb = steptl / rln;
    lambda = CNST(1.0);

    /*	check if new iterate satisfactory.  generate new lambda if necessary. */

    while(*iretcd > 1) {
	    for (i = 0; i < m; ++i)
	      xpls[i] = x[i] + lambda * p[i];

      /* evaluate function at new point */
      (*func)(xpls, state.hx, m, state.n, state.adata);
      for(i=0, tmp1=0.0; i<state.n; ++i){
        state.hx[i]=tmp2=state.x[i]-state.hx[i];
        tmp1+=tmp2*tmp2;
      }
      fpls=CNST(0.5)*tmp1; *ffpls=tmp1; ++(*(state.nfev));

	    if (fpls <= f + slp * alpha * lambda) { /* solution found */
	      *iretcd = 0;
	      if (lambda == CNST(1.) && sln > stepmx * CNST(.99)) *mxtake = 1;
	      return;
	    }

	    /* else : solution not (yet) found */

      /* First find a point with a finite value */

	    if (lambda < rmnlmb) {
	      /* no satisfactory xpls found sufficiently distinct from x */

	      *iretcd = 1;
	      return;
	    }
	    else { /*	calculate new lambda */

	      /* modifications to cover non-finite values */
	      if (fpls >= LM_REAL_MAX) {
		      lambda *= CNST(0.1);
		      firstback = 1;
	      }
	      else {
		      if (firstback) { /*	first backtrack: quadratic fit */
		        tlmbda = -lambda * slp / ((fpls - f - slp) * CNST(2.));
		        firstback = 0;
		      }
		      else { /*	all subsequent backtracks: cubic fit */
		        t1 = fpls - f - lambda * slp;
		        t2 = pfpls - f - plmbda * slp;
		        t3 = CNST(1.) / (lambda - plmbda);
		        a3 = CNST(3.) * t3 * (t1 / (lambda * lambda)
				      - t2 / (plmbda * plmbda));
		        b = t3 * (t2 * lambda / (plmbda * plmbda)
			          - t1 * plmbda / (lambda * lambda));
		        disc = b * b - a3 * slp;
		        if (disc > b * b)
			    /* only one positive critical point, must be minimum */
			        tlmbda = (-b + ((a3 < 0)? -(LM_REAL)sqrt(disc): (LM_REAL)sqrt(disc))) /a3;
		        else
			    /* both critical points positive, first is minimum */
			        tlmbda = (-b + ((a3 < 0)? (LM_REAL)sqrt(disc): -(LM_REAL)sqrt(disc))) /a3;

		        if (tlmbda > lambda * CNST(.5))
			        tlmbda = lambda * CNST(.5);
		    }
		    plmbda = lambda;
		    pfpls = fpls;
		    if (tlmbda < lambda * CNST(.1))
		      lambda *= CNST(.1);
		    else
		      lambda = tlmbda;
      }
	  }
  }
} /* LNSRCH */