int LEVMAR_DER(
  void (*func)(LM_REAL *p, LM_REAL *hx, int m, int n, void *adata), /* functional relation describing measurements. A p \in R^m yields a \hat{x} \in  R^n */
  void (*jacf)(LM_REAL *p, LM_REAL *j, int m, int n, void *adata),  /* function to evaluate the jacobian \part x / \part p */ 
  LM_REAL *p,         /* I/O: initial parameter estimates. On output has the estimated solution */
  LM_REAL *x,         /* I: measurement vector */
  int m,              /* I: parameter vector dimension (i.e. #unknowns) */
  int n,              /* I: measurement vector dimension */
  int itmax,          /* I: maximum number of iterations */
  LM_REAL opts[4],    /* I: minim. options [\mu, \epsilon1, \epsilon2, \epsilon3]. Respectively the scale factor for initial \mu,
                       * stopping thresholds for ||J^T e||_inf, ||Dp||_2 and ||e||_2. Set to NULL for defaults to be used
                       */
  LM_REAL info[LM_INFO_SZ],
					           /* O: information regarding the minimization. Set to NULL if don't care
                      * info[0]= ||e||_2 at initial p.
                      * info[1-4]=[ ||e||_2, ||J^T e||_inf,  ||Dp||_2, mu/max[J^T J]_ii ], all computed at estimated p.
                      * info[5]= # iterations,
                      * info[6]=reason for terminating: 1 - stopped by small gradient J^T e
                      *                                 2 - stopped by small Dp
                      *                                 3 - stopped by itmax
                      *                                 4 - singular matrix. Restart from current p with increased mu 
                      *                                 5 - no further error reduction is possible. Restart with increased mu
                      *                                 6 - stopped by small ||e||_2
                      * info[7]= # function evaluations
                      * info[8]= # jacobian evaluations
                      */
  LM_REAL *work,     /* working memory, allocate if NULL */
  LM_REAL *covar,    /* O: Covariance matrix corresponding to LS solution; mxm. Set to NULL if not needed. */
  void *adata)       /* pointer to possibly additional data, passed uninterpreted to func & jacf.
                      * Set to NULL if not needed
                      */
{
register int i, j, k, l;
int worksz, freework=0, issolved;
/* temp work arrays */
LM_REAL *e,          /* nx1 */
       *hx,         /* \hat{x}_i, nx1 */
       *jacTe,      /* J^T e_i mx1 */
       *jac,        /* nxm */
       *jacTjac,    /* mxm */
       *Dp,         /* mx1 */
   *diag_jacTjac,   /* diagonal of J^T J, mx1 */
       *pDp;        /* p + Dp, mx1 */

register LM_REAL mu,  /* damping constant */
                tmp; /* mainly used in matrix & vector multiplications */
LM_REAL p_eL2, jacTe_inf, pDp_eL2; /* ||e(p)||_2, ||J^T e||_inf, ||e(p+Dp)||_2 */
LM_REAL p_L2, Dp_L2=LM_REAL_MAX, dF, dL;
LM_REAL tau, eps1, eps2, eps2_sq, eps3;
LM_REAL init_p_eL2;
int nu=2, nu2, stop, nfev, njev=0;
const int nm=n*m;

  mu=jacTe_inf=0.0; /* -Wall */

  if(n<m){
    fprintf(stderr, LCAT(LEVMAR_DER, "(): cannot solve a problem with fewer measurements [%d] than unknowns [%d]\n"), n, m);
    return -1;
  }

  if(!jacf){
    fprintf(stderr, RCAT("No function specified for computing the jacobian in ", LEVMAR_DER)
        RCAT("().\nIf no such function is available, use ", LEVMAR_DIF) RCAT("() rather than ", LEVMAR_DER) "()\n");
    return -1;
  }

  if(opts){
	  tau=opts[0];
	  eps1=opts[1];
	  eps2=opts[2];
	  eps2_sq=opts[2]*opts[2];
    eps3=opts[3];
  }
  else{ // use default values
	  tau=CNST(LM_INIT_MU);
	  eps1=CNST(LM_STOP_THRESH);
	  eps2=CNST(LM_STOP_THRESH);
	  eps2_sq=CNST(LM_STOP_THRESH)*CNST(LM_STOP_THRESH);
    eps3=CNST(LM_STOP_THRESH);
  }

  if(!work){
    worksz=LM_DER_WORKSZ(m, n); //2*n+4*m + n*m + m*m;
    work=(LM_REAL *)malloc(worksz*sizeof(LM_REAL)); /* allocate a big chunk in one step */
    if(!work){
      fprintf(stderr, LCAT(LEVMAR_DER, "(): memory allocation request failed\n"));
      return -1;
    }
    freework=1;
  }

  /* set up work arrays */
  e=work;
  hx=e + n;
  jacTe=hx + n;
  jac=jacTe + m;
  jacTjac=jac + nm;
  Dp=jacTjac + m*m;
  diag_jacTjac=Dp + m;
  pDp=diag_jacTjac + m;

  /* compute e=x - f(p) and its L2 norm */
  (*func)(p, hx, m, n, adata); nfev=1;
  for(i=0, p_eL2=0.0; i<n; ++i){
    e[i]=tmp=x[i]-hx[i];
    p_eL2+=tmp*tmp;
  }
  init_p_eL2=p_eL2;

  for(k=stop=0; k<itmax && !stop; ++k){
    /* Note that p and e have been updated at a previous iteration */

    if(p_eL2<=eps3){ /* error is small */
      stop=6;
      break;
    }

    /* Compute the jacobian J at p,  J^T J,  J^T e,  ||J^T e||_inf and ||p||^2.
     * Since J^T J is symmetric, its computation can be speeded up by computing
     * only its upper triangular part and copying it to the lower part
     */

    (*jacf)(p, jac, m, n, adata); ++njev;

    /* J^T J, J^T e */
    if(nm<__BLOCKSZ__SQ){ // this is a small problem
      /* This is the straightforward way to compute J^T J, J^T e. However, due to
       * its noncontinuous memory access pattern, it incures many cache misses when
       * applied to large minimization problems (i.e. problems involving a large
       * number of free variables and measurements), in which J is too large to
       * fit in the L1 cache. For such problems, a cache-efficient blocking scheme
       * is preferable.
       *
       * Thanks to John Nitao of Lawrence Livermore Lab for pointing out this
       * performance problem.
       *
       * On the other hand, the straightforward algorithm is faster on small
       * problems since in this case it avoids the overheads of blocking. 
       */

      for(i=0; i<m; ++i){
        for(j=i; j<m; ++j){
          int lm;

          for(l=0, tmp=0.0; l<n; ++l){
            lm=l*m;
            tmp+=jac[lm+i]*jac[lm+j];
          }

		      /* store tmp in the corresponding upper and lower part elements */
          jacTjac[i*m+j]=jacTjac[j*m+i]=tmp;
        }

        /* J^T e */
        for(l=0, tmp=0.0; l<n; ++l)
          tmp+=jac[l*m+i]*e[l];
        jacTe[i]=tmp;
      }
    }
    else{ // this is a large problem
      /* Cache efficient computation of J^T J based on blocking
       */
      TRANS_MAT_MAT_MULT(jac, jacTjac, n, m);

      /* cache efficient computation of J^T e */
      for(i=0; i<m; ++i)
        jacTe[i]=0.0;

      for(i=0; i<n; ++i){
        register LM_REAL *jacrow;

        for(l=0, jacrow=jac+i*m, tmp=e[i]; l<m; ++l)
          jacTe[l]+=jacrow[l]*tmp;
      }
    }

	  /* Compute ||J^T e||_inf and ||p||^2 */
    for(i=0, p_L2=jacTe_inf=0.0; i<m; ++i){
      if(jacTe_inf < (tmp=FABS(jacTe[i]))) jacTe_inf=tmp;

      diag_jacTjac[i]=jacTjac[i*m+i]; /* save diagonal entries so that augmentation can be later canceled */
      p_L2+=p[i]*p[i];
    }
    //p_L2=sqrt(p_L2);

#if 0
if(!(k%10)){
  printf("Iter: %d, estimate: ", k);
  for(i=0; i<m; ++i)
    printf("%.9g ", p[i]);
  printf("-- errors %.9g %0.9g\n", jacTe_inf, p_eL2);
}
#endif

    /* check for convergence */
    if((jacTe_inf <= eps1)){
      Dp_L2=0.0; /* no increment for p in this case */
      stop=1;
      break;
    }

   /* compute initial damping factor */
    if(k==0){
      for(i=0, tmp=LM_REAL_MIN; i<m; ++i)
        if(diag_jacTjac[i]>tmp) tmp=diag_jacTjac[i]; /* find max diagonal element */
      mu=tau*tmp;
    }

    /* determine increment using adaptive damping */
    while(1){
      /* augment normal equations */
      for(i=0; i<m; ++i)
        jacTjac[i*m+i]+=mu;

      /* solve augmented equations */
#ifdef HAVE_LAPACK
      /* 5 alternatives are available: LU, Cholesky, 2 variants of QR decomposition and SVD.
       * Cholesky is the fastest but might be inaccurate; QR is slower but more accurate;
       * SVD is the slowest but most accurate; LU offers a tradeoff between accuracy and speed
       */

      issolved=AX_EQ_B_LU(jacTjac, jacTe, Dp, m);
      //issolved=AX_EQ_B_CHOL(jacTjac, jacTe, Dp, m);
      //issolved=AX_EQ_B_QR(jacTjac, jacTe, Dp, m);
      //issolved=AX_EQ_B_QRLS(jacTjac, jacTe, Dp, m, m);
      //issolved=AX_EQ_B_SVD(jacTjac, jacTe, Dp, m);

#else
      /* use the LU included with levmar */
      issolved=AX_EQ_B_LU(jacTjac, jacTe, Dp, m);
#endif /* HAVE_LAPACK */

      if(issolved){
        /* compute p's new estimate and ||Dp||^2 */
        for(i=0, Dp_L2=0.0; i<m; ++i){
          pDp[i]=p[i] + (tmp=Dp[i]);
          Dp_L2+=tmp*tmp;
        }
        //Dp_L2=sqrt(Dp_L2);

        if(Dp_L2<=eps2_sq*p_L2){ /* relative change in p is small, stop */
        //if(Dp_L2<=eps2*(p_L2 + eps2)){ /* relative change in p is small, stop */
          stop=2;
          break;
        }

       if(Dp_L2>=(p_L2+eps2)/(CNST(EPSILON)*CNST(EPSILON))){ /* almost singular */
       //if(Dp_L2>=(p_L2+eps2)/CNST(EPSILON)){ /* almost singular */
         stop=4;
         break;
       }

        (*func)(pDp, hx, m, n, adata); ++nfev; /* evaluate function at p + Dp */
        for(i=0, pDp_eL2=0.0; i<n; ++i){ /* compute ||e(pDp)||_2 */
          hx[i]=tmp=x[i]-hx[i];
          pDp_eL2+=tmp*tmp;
        }

        for(i=0, dL=0.0; i<m; ++i)
          dL+=Dp[i]*(mu*Dp[i]+jacTe[i]);

        dF=p_eL2-pDp_eL2;

        if(dL>0.0 && dF>0.0){ /* reduction in error, increment is accepted */
          tmp=(CNST(2.0)*dF/dL-CNST(1.0));
          tmp=CNST(1.0)-tmp*tmp*tmp;
          mu=mu*( (tmp>=CNST(ONE_THIRD))? tmp : CNST(ONE_THIRD) );
          nu=2;

          for(i=0 ; i<m; ++i) /* update p's estimate */
            p[i]=pDp[i];

          for(i=0; i<n; ++i) /* update e and ||e||_2 */
            e[i]=hx[i];
          p_eL2=pDp_eL2;
          break;
        }
      }

      /* if this point is reached, either the linear system could not be solved or
       * the error did not reduce; in any case, the increment must be rejected
       */

      mu*=nu;
      nu2=nu<<1; // 2*nu;
      if(nu2<=nu){ /* nu has wrapped around (overflown). Thanks to Frank Jordan for spotting this case */
        stop=5;
        break;
      }
      nu=nu2;

      for(i=0; i<m; ++i) /* restore diagonal J^T J entries */
        jacTjac[i*m+i]=diag_jacTjac[i];
    } /* inner loop */
  }

  if(k>=itmax) stop=3;

  for(i=0; i<m; ++i) /* restore diagonal J^T J entries */
    jacTjac[i*m+i]=diag_jacTjac[i];

  if(info){
    info[0]=init_p_eL2;
    info[1]=p_eL2;
    info[2]=jacTe_inf;
    info[3]=Dp_L2;
    for(i=0, tmp=LM_REAL_MIN; i<m; ++i)
      if(tmp<jacTjac[i*m+i]) tmp=jacTjac[i*m+i];
    info[4]=mu/tmp;
    info[5]=(LM_REAL)k;
    info[6]=(LM_REAL)stop;
    info[7]=(LM_REAL)nfev;
    info[8]=(LM_REAL)njev;
  }

  /* covariance matrix */
  if(covar){
    LEVMAR_COVAR(jacTjac, covar, p_eL2, m, n);
  }

  if(freework) free(work);

  return (stop!=4)?  k : -1;
}