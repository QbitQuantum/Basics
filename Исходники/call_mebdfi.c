SEXP call_mebdfi(SEXP y, SEXP yprime, SEXP times, SEXP resfunc, SEXP parms,
		SEXP rtol, SEXP atol, SEXP itol, SEXP rho, SEXP Tcrit, SEXP Hini,
    SEXP Maxord, SEXP maxIt, SEXP nind, SEXP jacfunc, SEXP initfunc,
    SEXP verbose, SEXP Mf, SEXP Mbnd, SEXP Liw, SEXP Lrw,
    SEXP nOut, SEXP Rpar, SEXP Ipar, SEXP flist, SEXP Funtype, SEXP Mass)
{
/******************************************************************************/
/******                   DECLARATION SECTION                            ******/
/******************************************************************************/

/* These R-structures will be allocated and returned to R*/
  SEXP   yout, yout2=NULL, dyout=NULL, ISTATE, RWORK;
  int    i, j, k, nt, latol, lrtol, lrw, liw, isDll;
  int    isForcing , Itol, *mbnd, mf, maxord, isOut;
  double *xytmp,  *xdytmp, *rwork, tin, tout, *Atol, *Rtol, tcrit, hini;
  double *delta=NULL, cj;
  int    idid, *iwork, ires, ierr, funtype;

  C_res_func_type  *res_func = NULL;
  C_jac_func_type  *jac_func = NULL;

/******************************************************************************/
/******                         STATEMENTS                               ******/
/******************************************************************************/

/*                      #### initialisation ####                              */    

  init_N_Protect();


  n_eq = LENGTH(y);
  nt = LENGTH(times);
//  mflag = INTEGER(verbose)[0];        
  nout  = INTEGER(nOut)[0];
  funtype  = INTEGER(Funtype)[0]; /* 1 = res, 2 = func */

  ntot  = n_eq;

  mf = INTEGER(Mf)[0];
  maxord = INTEGER(Maxord)[0];

  tcrit = REAL(Tcrit)[0];
  hini = REAL(Hini)[0];
  ierr = 0;

/* function is a dll ?*/
  if (inherits(resfunc, "NativeSymbol"))
    isDll = 1;
  else
    isDll = 0;

  isOut = 0;
  if (isDll == 0 && nout > 0) isOut =1;
  else if (isDll == 1 ) ntot = ntot+ nout;

/* initialise output vectors ... */
  if (isDll==1)  { /* function is a dll */
    lrpar = nout + LENGTH(Rpar);       /* length of rpar */
    lipar = 3    + LENGTH(Ipar);       /* length of ipar */
  } else  {                             /* function is not a dll */
    lipar = 1;
    lrpar = 1;
  }

  out   = (double *) R_alloc(lrpar, sizeof(double));
  ipar  = (int *)    R_alloc(lipar, sizeof(int));

  if (isDll ==1)  {
    ipar[0] = nout;          /* first 3 elements of ipar are special */
    ipar[1] = lrpar;
    ipar[2] = lipar;
    /* other elements of ipar are set in R-function lsodx via argument *ipar* */
    for (j = 0; j < LENGTH(Ipar); j++) ipar[j+3] = INTEGER(Ipar)[j];

    /* first nout elements of rpar reserved for output variables
      other elements are set in R-function lsodx via argument *rpar* */
    for (j = 0; j < nout;        j++) out[j] = 0.;
    for (j = 0; j < LENGTH(Rpar);j++) out[nout+j] = REAL(Rpar)[j];
  } else {
    for (j = 0; j < lrpar;       j++) out[j] = 0.;
    for (j = 0; j < lipar;       j++) ipar[j] = 0.;
  }

  /* copies of all variables that will be changed in the FORTRAN subroutine */
  xytmp = (double *) R_alloc(n_eq, sizeof(double));
   for (j = 0; j < n_eq; j++) xytmp[j] = REAL(y)[j];

  xdytmp = (double *) R_alloc(n_eq, sizeof(double));
   for (j = 0; j < n_eq; j++) xdytmp[j] = REAL(yprime)[j];

  /* tolerance */
  latol = LENGTH(atol);
  Atol  = (double *) R_alloc((int) latol, sizeof(double));
    for (j = 0; j < latol; j++) Atol[j] = REAL(atol)[j];

  lrtol = LENGTH(rtol);
  Rtol  = (double *) R_alloc((int) lrtol, sizeof(double));
    for (j = 0; j < lrtol; j++) Rtol[j] = REAL(rtol)[j];

  Itol  = INTEGER(itol)[0];

  /* work arrays */
  liw = INTEGER(Liw)[0];
  iwork = (int *) R_alloc(liw, sizeof(int));
  for (j = 0; j<3; j++) iwork[j] = INTEGER(nind)[j];
  for (j = 3; j<liw; j++) iwork[j] = 0;
  iwork[13] = INTEGER(maxIt)[0];

  lrw =  INTEGER(Lrw)[0];
  rwork = (double *) R_alloc(lrw, sizeof(double));
  for (j = 0; j < lrw; j++) rwork[j] = 0.;
  rwork[0] = DBL_EPSILON;

  mbnd  = (int *) R_alloc(4, sizeof(int));
  for (j = 0; j<4; j++) mbnd[j] = INTEGER(Mbnd)[j];
  nrowpd = mbnd[3];

  /* initialise global variables... */

  PROTECT(Rin  = NEW_NUMERIC(2));                    incr_N_Protect();
  PROTECT(Y = allocVector(REALSXP,n_eq));            incr_N_Protect();
  PROTECT(YPRIME = allocVector(REALSXP,n_eq));       incr_N_Protect();
  PROTECT(yout = allocMatrix(REALSXP,ntot+1,nt));    incr_N_Protect();
  if (isOut == 1) {
    PROTECT(dyout = allocMatrix(REALSXP,n_eq+1,nt));    incr_N_Protect();
  }
  
  /**************************************************************************/
  /****** Initialization of Parameters and Forcings (DLL functions)    ******/
  /**************************************************************************/
  initParms(initfunc, parms);
    //  error("till here");

  isForcing = initForcings(flist);

/* pointers to functions passed to the FORTRAN subroutine                    */
  isMass = 0;
  if (isDll == 1)  {       /* DLL address passed to fortran */
      if (funtype == 1) {
        res_func = (C_res_func_type *) R_ExternalPtrAddrFn_(resfunc);
         if(isForcing==1) {
           DLL_res_func = (C_res_func_type *) R_ExternalPtrAddrFn_(resfunc);
           res_func = (C_res_func_type *) DLL_res_func_forc;
         }

      } else if (funtype <= 3) {
        res_func = DLL_res_ode;
        DLL_deriv_func = (C_deriv_func_type *) R_ExternalPtrAddrFn_(resfunc);
        if(isForcing==1)
          res_func = (C_res_func_type *) DLL_res_func_forc2;
        if (funtype == 3) {    /* mass matrix */
          isMass = 1;
          mass = (double *)R_alloc(n_eq * n_eq, sizeof(double));
          for (j = 0; j < n_eq * n_eq; j++) mass[j] = REAL(Mass)[j];
          dytmp = (double *) R_alloc(n_eq, sizeof(double));
        }
      } else                  /* for MASS matrix .... */
       error("DLL function type not yet implemented");

      delta = (double *) R_alloc(n_eq, sizeof(double));
      for (j = 0; j < n_eq; j++) delta[j] = 0.;


    } else {
      /* interface function between fortran and R passed to Fortran*/     
      res_func = (C_res_func_type *) C_res_func;
      /* needed to communicate with R */      
      PROTECT(R_res_func = resfunc);               incr_N_Protect();
      PROTECT(R_envir = rho);                  incr_N_Protect();

    }
  if (!isNull(jacfunc))
    {
      if (inherits(jacfunc,"NativeSymbol"))
	      jac_func = (C_jac_func_type *) R_ExternalPtrAddrFn_(jacfunc);
      else  {
	      jac_func = (C_jac_func_type *) C_jac_func;
	      PROTECT(R_daejac_func = jacfunc);         incr_N_Protect();
	    }
    }
/*                      #### initial time step ####                           */
  idid = 1;
  REAL(yout)[0] = REAL(times)[0];
  for (j = 0; j < n_eq; j++)
      REAL(yout)[j+1] = REAL(y)[j];

  if (nout>0)  {
     tin = REAL(times)[0];

	   if (isDll == 1) {
       res_func (&tin, xytmp, xdytmp, &cj, delta, &ires, out, ipar) ;
//      for (j = 0; j < nout; j++)
//	      REAL(yout)[n_eq + j + 1] = out[j];
     }
	   else for (j = 0; j < n_eq; j++)
	      REAL(dyout)[j] = xdytmp[j];
  }
/*                     ####   main time loop   ####                           */


  for (i = 0; i < nt-1; i++)
  {
//
	  tin = REAL(times)[i];
      tout = REAL(times)[i+1];
//      Rprintf("idid %i tin %g tout %g xdytmp %g \n", idid, tin, tout, xdytmp[0]);
      F77_CALL(mebdfi)(&n_eq, &tin, &hini, xytmp, xdytmp, &tout, &tcrit,
        &mf, &idid, &lrw, rwork, &liw, iwork, mbnd, &maxord,
	      &Itol, Rtol, Atol, out, ipar,  jac_func, res_func, &ierr);
//	   Rprintf(" hini, xytmp %g %g %g %g %g %g\n", hini, xytmp[0], xytmp[1],xytmp[2] ,xytmp[3], xytmp[4] );
//   error("here");
     if (idid == 1) {
        idid = 0;
        F77_CALL(mebdfi)(&n_eq, &tin, &hini, xytmp, xdytmp, &tout, &tcrit,
         &mf, &idid, &lrw, rwork, &liw, iwork, mbnd, &maxord,
	       &Itol, Rtol, Atol, out, ipar,  jac_func, res_func, &ierr);
      }
//     Rprintf("idid %i tin %g tout %g tin-tout %g \n", idid, tin, tout, tin-tout);

	    if (idid == -1)   {
	      warning("the integration failed to pass the error test, even after reducing h by factor 1e10");
	    }   else    if (idid == -2)   {
	      warning("the integration failed by repeated error test failures or by a test on rtol/atol. too much accuracy requested");
      }   else    if (idid == -3)   {
	      warning("the integration failed to achieve corrector convergence, even after reducing h by factor 1e10");
      }  else    if (idid == -4)    {
       warning("illegal values of input parameters - see printed message");
      }  else    if (idid == -5)    {
       warning("idid was -1 on input, but tout was not beyond t");
      }  else    if (idid == -6)    {
       warning("maximum number of integration steps exceeded");
      }  else    if (idid == -7)   {
       warning("stepsize is too small, < sqrt(uround)/100");
      }  else    if (idid == -11)   {
       warning("insufficient real workspace for the integration");
      }  else    if (idid == -12)   {
       warning("insufficient integer workspace for the integration");

      }
  // Rprintf(" i, tin, tout, ntot %i, %g, %g, %i\n", i, tin, tout, ntot);

 	  REAL(yout)[(i+1)*(ntot+1)] = tin;
	  for (j = 0; j < n_eq; j++)
	    REAL(yout)[(i+1)*(ntot + 1) + j + 1] = xytmp[j];

    if (nout>0) {
	    if (isDll == 1) {
        res_func (&tin, xytmp, xdytmp, &cj, delta, &ires, out, ipar) ;
       for (j = 0; j < nout; j++)
	      REAL(yout)[(i+1)*(ntot + 1) + n_eq + j + 1] = out[j];
      }
	    else for (j = 0; j < n_eq; j++)
	      REAL(dyout)[(i+1)*(n_eq) + j + 1] = xdytmp[j];
    }
/**/
/*                    ####  an error occurred   ####                          */                     
    if (tin < tout) {
     if (idid >=0) idid = -10;
	   warning("Returning early from mebdfi  Results are accurate, as far as they go\n");

	/* redimension yout */
   	PROTECT(yout2 = allocMatrix(REALSXP,ntot+1,(i+2)));incr_N_Protect();
  	for (k = 0; k < i+2; k++)
	   for (j = 0; j < ntot+1; j++)
	    REAL(yout2)[k*(ntot+1) + j] = REAL(yout)[k*(ntot+1) + j];
	   break;
    }
  }    /* end main time loop */


/*     error("tillhere");
                ####   returning output   ####                           */

  PROTECT(ISTATE = allocVector(INTSXP, 15));incr_N_Protect();
  for (k = 0;k<14;k++) INTEGER(ISTATE)[k+1] = iwork[k];
  INTEGER(ISTATE)[0] = idid;


  PROTECT(RWORK = allocVector(REALSXP, 1));incr_N_Protect();
  REAL(RWORK)[0] = rwork[1];

  if (idid >= 0)
    {
      setAttrib(yout, install("istate"), ISTATE);
      setAttrib(yout, install("rstate"), RWORK);    
      if (isOut ==1) setAttrib(yout, install("dy"), dyout);
    }
  else
    {
      setAttrib(yout2, install("istate"), ISTATE);
      setAttrib(yout2, install("rstate"), RWORK);   
      if (isOut ==1) setAttrib(yout2, install("dy"), dyout);
    }
//

/*                       ####   termination   ####                            */       
  unprotect_all();
  if (idid >= 0)
    return(yout);
  else
    return(yout2);
}