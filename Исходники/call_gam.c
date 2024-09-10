SEXP call_gambim(SEXP y, SEXP times, SEXP derivfunc, SEXP parms, SEXP rtol,
		SEXP atol, SEXP rho, SEXP Tcrit, SEXP jacfunc, SEXP initfunc,
    SEXP verbose, SEXP LRW, SEXP rWork, SEXP iWork, SEXP jT,
    SEXP nOut, SEXP Nrmas, SEXP masfunc, SEXP ML, SEXP MU, SEXP Hini,
    SEXP Rpar, SEXP Ipar, SEXP flist, SEXP Type)

{
/******************************************************************************/
/******                   DECLARATION SECTION                            ******/
/******************************************************************************/

  int  j, nt, latol, lrtol, imas, mlmas, mumas, type;
  int  isForcing, runOK;
  double *Atol, *Rtol, hini;
  int itol, ijac, ml, mu, iout, idid, liw, lrw, sum;

  /* pointers to functions passed to FORTRAN */
  C_jac_func_type_gb    *jac_func_gb = NULL;
  C_solout_type         *solout = NULL;
  C_solout_type_bim     *solout_bim = NULL;
  C_mas_type            *mas_func = NULL;

/******************************************************************************/
/******                         STATEMENTS                               ******/
/******************************************************************************/

/*                      #### initialisation ####                              */
  init_N_Protect();

  type  = INTEGER(Type)[0];     /* jacobian type */
  ijac  = INTEGER(jT)[0];       /* jacobian type */
  n_eq = LENGTH(y);             /* number of equations */
  nt   = LENGTH(times);         /* number of output times */
  maxt = nt;

  tt = (double *) R_alloc(nt, sizeof(double));
  for (j = 0; j < nt; j++) tt[j] = REAL(times)[j];

//  mflag = INTEGER(verbose)[0];

  /* is function a dll ?*/
  isDll = inherits(derivfunc, "NativeSymbol");

  /* initialise output ... */
  initOutC(isDll, n_eq, nOut, Rpar, Ipar);

  /* copies of variables that will be changed in the FORTRAN subroutine */
  xytmp = (double *) R_alloc(n_eq, sizeof(double));
  for (j = 0; j < n_eq; j++) xytmp[j] = REAL(y)[j];

  ytmp = (double *) R_alloc(n_eq, sizeof(double));
  for (j = 0; j < n_eq; j++) ytmp[j] = 0.;

  latol = LENGTH(atol);
  Atol = (double *) R_alloc((int) latol, sizeof(double));
  for (j = 0; j < latol; j++) Atol[j] = REAL(atol)[j];

  lrtol = LENGTH(rtol);
  Rtol = (double *) R_alloc((int) lrtol, sizeof(double));
  for (j = 0; j < lrtol; j++) Rtol[j] = REAL(rtol)[j];

  /* tolerance specifications */
  if (latol == 1 ) itol = 0;
  else             itol = 1;

  /* mass matrix */
  imas  = INTEGER(Nrmas)[0];
  mlmas = INTEGER(Nrmas)[1];
  mumas = INTEGER(Nrmas)[2];

  /* work vectors */
  if (type == 1) {
    liw = 27;
    lrw = 21;
  } else  {       //  if (type == 2)
    liw = n_eq + 40;
    lrw = INTEGER(LRW)[0];
 }

  iwork = (int *) R_alloc(liw, sizeof(int));
  for (j=0; j<LENGTH(iWork); j++) iwork[j] = INTEGER(iWork)[j];
  for (j=LENGTH(iWork); j<liw; j++) iwork[j] = 0;

  rwork = (double *) R_alloc(lrw, sizeof(double));
  for (j=0; j<length(rWork); j++) rwork[j] = REAL(rWork)[j];
  for (j=length(rWork); j<lrw; j++) rwork[j] = 0.;

  ml = INTEGER(ML)[0];
  mu = INTEGER(MU)[0];
  hini = REAL(Hini)[0];

  /* initialise global R-variables...  */
  initglobals (nt);

  /* Initialization of Parameters, Forcings (DLL) */
  initParms(initfunc, parms);
  isForcing = initForcings(flist);

  if (nout > 0 ) {
     xdytmp= (double *) R_alloc(n_eq, sizeof(double));
     for (j = 0; j < n_eq; j++) xdytmp[j] = 0.;
  }

 /* pointers to functions deriv_func, jac_func, jac_vec, root_func, passed to FORTRAN */
  if (isDll)  { /* DLL address passed to FORTRAN */
      deriv_func = (C_deriv_func_type *) R_ExternalPtrAddrFn_(derivfunc);

 	   /* overruling deriv_func if forcing */
      if (isForcing) {
        DLL_deriv_func = deriv_func;
        deriv_func = (C_deriv_func_type *) C_deriv_func_forc_gb;
      }
  } else {
      /* interface function between FORTRAN and C/R passed to FORTRAN */
      deriv_func = (C_deriv_func_type *) C_deriv_func_gb;
      /* needed to communicate with R */
      R_deriv_func = derivfunc;
      R_envir = rho;
  }

  if (!isNull(jacfunc))   {
      if (isDll)
	      jac_func_gb = (C_jac_func_type_gb *) R_ExternalPtrAddrFn_(jacfunc);
	    else  {
	      R_jac_func = jacfunc;
	      jac_func_gb= C_jac_func_gb;
	    }
    }

  if (!isNull(masfunc))   {
	      R_mas_func = masfunc;
	      mas_func= C_mas_func;
  }

  solout = C_solout_gam;
  solout_bim = C_solout_bim;
  iout = 1;                           /* solout used */
  idid = 0;

/*                   ####      integration     ####                           */
  it   = 0;
  tin  = REAL(times)[0];
  tout = REAL(times)[nt-1];

  saveOut (tin, xytmp);               /* save initial condition */
  it = it +1;

  if (type == 1)
    F77_CALL(gamd) ( &n_eq, deriv_func, &tin, xytmp, &tout, &hini,
		     Rtol, Atol, &itol, jac_func_gb, &ijac, &ml, &mu,
         mas_func, &imas, &mlmas, &mumas, solout, &iout,
		     rwork, &lrw, iwork, &liw, out, ipar, &idid);
  else if (type == 2)
    F77_CALL(bimd) ( &n_eq, deriv_func, &tin, &tout, xytmp, &hini,
		     Rtol, Atol, &itol, jac_func_gb, &ijac, &ml, &mu,
         mas_func, &imas, &mlmas, &mumas, solout_bim, &iout,
		     rwork, &lrw, iwork, &liw, out, ipar, &idid);


  if (idid == -1)
     warning("input is not consistent");
  else if (idid == -2)
     warning("larger maxsteps needed");
  else if (idid == -3)
     warning("step size becomes too small");
  else if (idid == -4)
     warning("matrix is repeatedly singular");

/*                   ####  an error occurred   ####                           */
  if(it <= nt-1) saveOut (tin, xytmp);              /* save final condition */
  if (idid < 0 ) {
    it = it-1;
    returnearly (1);
  }

/*                   ####   returning output   ####                           */

/* feval */

  PROTECT(RWORK = allocVector(REALSXP, 3)); incr_N_Protect();
  REAL(RWORK)[0] = hini;
  REAL(RWORK)[1] = hini;

  REAL(RWORK)[2] = tin;

  PROTECT(ISTATE = allocVector(INTSXP, 6)); incr_N_Protect();
  INTEGER(ISTATE)[0] = idid;

/* nsteps */
  sum = 0;
  runOK = 0;
  if (type == 1)  {
    for (j = 11; j < 23; j++) sum = sum + iwork[j];
    INTEGER(ISTATE)[1] = sum;

/* feval */
    INTEGER(ISTATE)[2] = iwork[9];

/* jacobian eval */
    INTEGER(ISTATE)[3] = iwork[10];

/* LU decomp */
    INTEGER(ISTATE)[4] = iwork[23];

/* number rejected steps */
    sum = 0;
    for (j = 11; j < 15; j++) sum = sum + iwork[j];
    INTEGER(ISTATE)[5] = INTEGER(ISTATE)[1]- sum;
	if(idid > 0) runOK = 1;
  } else {
    for (j = 20; j < 25; j++) sum = sum + iwork[j];
    INTEGER(ISTATE)[1] = sum;

/* feval */
    INTEGER(ISTATE)[2] = iwork[11];

/* jacobian eval */
    INTEGER(ISTATE)[3] = iwork[12];

/* LU decomp */
    INTEGER(ISTATE)[4] = iwork[13];

/* number rejected steps */
    sum = 0;
    for (j = 25; j < 29; j++) sum = sum + iwork[j];
    INTEGER(ISTATE)[5] = INTEGER(ISTATE)[1]- sum;
    if(idid >= 0)  runOK = 1;

}


  if (runOK) {
    setAttrib(YOUT, install("istate"), ISTATE);
    setAttrib(YOUT, install("rstate"), RWORK);
  }
  else  {
    setAttrib(YOUT2, install("istate"), ISTATE);
    setAttrib(YOUT2, install("rstate"), RWORK);
  }

/*                   ####     termination      ####                           */
  unprotect_all();
  if (runOK)
    return(YOUT);
  else
    return(YOUT2);
}