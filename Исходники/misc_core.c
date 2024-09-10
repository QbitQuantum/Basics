/* central finite difference approximation to the jacobian of func */
void FDIF_CENT_JAC_APPROX(
    void (*func)(LM_REAL *p, LM_REAL *hx, int m, int n, void *adata),
													   /* function to differentiate */
    LM_REAL *p,              /* I: current parameter estimate, mx1 */
    LM_REAL *hxm,            /* W/O: work array for evaluating func(p-delta), nx1 */
    LM_REAL *hxp,            /* W/O: work array for evaluating func(p+delta), nx1 */
    LM_REAL delta,           /* increment for computing the jacobian */
    LM_REAL *jac,            /* O: array for storing approximated jacobian, nxm */
    int m,
    int n,
    void *adata)
{
register int i, j;
LM_REAL tmp;
register LM_REAL d;

  for(j=0; j<m; ++j){
    /* determine d=max(1E-04*|p[j]|, delta), see HZ */
    d=CNST(1E-04)*p[j]; // force evaluation
    d=FABS(d);
    if(d<delta)
      d=delta;

    tmp=p[j];
    p[j]-=d;
    (*func)(p, hxm, m, n, adata);

    p[j]=tmp+d;
    (*func)(p, hxp, m, n, adata);
    p[j]=tmp; /* restore */

    d=CNST(0.5)/d; /* invert so that divisions can be carried out faster as multiplications */
    for(i=0; i<n; ++i){
      jac[i*m+j]=(hxp[i]-hxm[i])*d;
    }
  }
}