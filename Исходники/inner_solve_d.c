int inner_solve_dprimme(double *x, double *r, double *rnorm, 
   double *evecs, double *evecsHat, double *UDU, int *ipivot, 
   double *xKinvx, double *Lprojector, double *RprojectorQ, 
   double *RprojectorX, int sizeLprojector, int sizeRprojectorQ, 
   int sizeRprojectorX, double *sol, double eval, double shift, 
   double eresTol, double aNormEstimate, double machEps, double *rwork, 
   int rworkSize, primme_params *primme) {

   int i;             /* loop variable                                      */
   int workSpaceSize; /* Size of local work array.                          */
   int numIts;        /* Number of inner iterations                         */
   int ret;           /* Return value used for error checking.              */
   int maxIterations; /* The maximum # iterations allowed. Depends on primme  */

   double *workSpace; /* Workspace needed by UDU routine */

   /* QMR parameters */

   double *g, *d, *delta, *w;
   double alpha_prev, beta, rho_prev, rho;
//   double ztmp;	// [RMS: unused]
   double Theta_prev, Theta, c, sigma_prev, tau_init, tau_prev, tau; 

   /* Parameters used to dynamically update eigenpair */
   double Beta, Delta, Psi, Beta_prev, Delta_prev, Psi_prev;
   double eta;

   double dot_sol, eval_updated, eval_prev, eres2_updated, eres_updated, R;
   double Gamma_prev, Phi_prev;
   double Gamma, Phi;
   double gamma;

   /* The convergence criteria of the inner linear system must satisfy:       */
   /* || current residual || <= relativeTolerance * || initial residual ||    */
   /*                                               + absoluteTol             */

   double relativeTolerance; 
   double absoluteTolerance;
   double LTolerance, ETolerance;

   /* Some constants 							      */
   double tpone = +1.0e+00, tzero = +0.0e+00;

   /* -------------------------------------------*/
   /* Subdivide the workspace into needed arrays */
   /* -------------------------------------------*/

   g      = rwork;
   d      = g + primme->nLocal;
   delta  = d + primme->nLocal;
   w      = delta + primme->nLocal;
   workSpace = w + primme->nLocal;  // This needs at least 2*numOrth+NumEvals)
   
   workSpaceSize = rworkSize - (int)(workSpace - rwork);
   
   /* -----------------------------------------*/
   /* Set up convergence criteria by Tolerance */
   /* -----------------------------------------*/

   if (primme->aNorm <= 0.0L) {
      absoluteTolerance = aNormEstimate*machEps;
      eresTol = eresTol*aNormEstimate;
   }
   else {
      absoluteTolerance = primme->aNorm*machEps;
   }
   tau_prev = tau_init = *rnorm;       /* Assumes zero initial guess */
   LTolerance = eresTol;

   // Andreas: note that eigenresidual tol may not be achievable, because we
   // iterate on P(A-s)P not (A-s). But tau reflects linSys on P(A-s)P.
   if (primme->correctionParams.convTest == primme_adaptive) {
      ETolerance = max(eresTol/1.8L, absoluteTolerance);
      LTolerance = ETolerance;
   }
   else if (primme->correctionParams.convTest == primme_adaptive_ETolerance) {
      LTolerance = max(eresTol/1.8L, absoluteTolerance);
      ETolerance = max(tau_init*0.1L, LTolerance);
   }
   else if (primme->correctionParams.convTest == primme_decreasing_LTolerance) {
      relativeTolerance = pow(primme->correctionParams.relTolBase, 
         (double)-primme->stats.numOuterIterations);
      LTolerance = relativeTolerance * tau_init 
	           + absoluteTolerance + eresTol;
     //printf(" RL %e INI %e abso %e LToler %e aNormEstimate %e \n",
     //relativeTolerance, tau_init, absoluteTolerance,LTolerance,aNormEstimate);
   }
   
   /* --------------------------------------------------------*/
   /* Set up convergence criteria by max number of iterations */
   /* --------------------------------------------------------*/

   /* compute first total number of remaining matvecs */

   maxIterations = primme->maxMatvecs - primme->stats.numMatvecs;

   /* Perform primme.maxInnerIterations, but do not exceed total remaining */
   if (primme->correctionParams.maxInnerIterations > 0) {

      maxIterations = min(primme->correctionParams.maxInnerIterations, 
		          maxIterations);
   }

   /* --------------------------------------------------------*/
   /* Rest of initializations                                 */
   /* --------------------------------------------------------*/

   /* Assume zero initial guess */
   Num_dcopy_dprimme(primme->nLocal, r, 1, g, 1);

   ret = apply_projected_preconditioner(g, evecs, RprojectorQ, 
	   x, RprojectorX, sizeRprojectorQ, sizeRprojectorX, 
	   xKinvx, UDU, ipivot, d, workSpace, primme);

   if (ret != 0) {
      primme_PushErrorMessage(Primme_inner_solve, 
         Primme_apply_projected_preconditioner, ret, __FILE__, __LINE__, 
         primme);
      return APPLYPROJECTEDPRECONDITIONER_FAILURE;
   }
      
   Theta_prev = 0.0L;
   eval_prev = eval;
   rho_prev = dist_dot(g, 1, d, 1, primme);
      
   /* Initialize recurrences used to dynamically update the eigenpair */

   Beta_prev = Delta_prev = Psi_prev = tzero;
   Gamma_prev = Phi_prev = 0.0L;

   /* other initializations */
   for (i = 0; i < primme->nLocal; i++) {
      delta[i] = tzero;
      sol[i] = tzero;
   }

   numIts = 0;
      
   /*----------------------------------------------------------------------*/
   /*------------------------ Begin Inner Loop ----------------------------*/
   /*----------------------------------------------------------------------*/

   while (numIts < maxIterations) {

      apply_projected_matrix(d, shift, Lprojector, sizeLprojector, 
		             w, workSpace, primme);
      sigma_prev = dist_dot(d, 1, w, 1, primme);

      if (sigma_prev == 0.0L) {
         if (primme->printLevel >= 5 && primme->procID == 0) {
            fprintf(primme->outputFile,"Exiting because SIGMA %e\n",sigma_prev);
         }
         break;
      }

      alpha_prev = rho_prev/sigma_prev;
      if (fabs(alpha_prev) < machEps || fabs(alpha_prev) > 1.0L/machEps){
         if (primme->printLevel >= 5 && primme->procID == 0) {
            fprintf(primme->outputFile,"Exiting because ALPHA %e\n",alpha_prev);
         }
	 break;
      }

      Num_axpy_dprimme(primme->nLocal, -alpha_prev, w, 1, g, 1);

      Theta = dist_dot(g, 1, g, 1, primme);
      Theta = sqrt(Theta);
      Theta = Theta/tau_prev;
      c = 1.0L/sqrt(1+Theta*Theta);
      tau = tau_prev*Theta*c;

      gamma = c*c*Theta_prev*Theta_prev;
      eta = alpha_prev*c*c;
      Num_scal_dprimme(primme->nLocal, gamma, delta, 1);
      Num_axpy_dprimme(primme->nLocal, eta, d, 1, delta, 1);
      Num_axpy_dprimme(primme->nLocal, tpone, delta, 1, sol, 1);
      numIts++;

      if (fabs(rho_prev) == 0.0L ) {
         if (primme->printLevel >= 5 && primme->procID == 0) {
            fprintf(primme->outputFile,"Exiting because abs(rho) %e\n",
	       fabs(rho_prev));
         }
         break;
      }
      
      if (tau < LTolerance) {
         if (primme->printLevel >= 5 && primme->procID == 0) {
            fprintf(primme->outputFile, " tau < LTol %e %e\n",tau, LTolerance);
         }
         break;
      }
      else if (primme->correctionParams.convTest == primme_adaptive_ETolerance
	    || primme->correctionParams.convTest == primme_adaptive) {
         /* --------------------------------------------------------*/
	 /* Adaptive stopping based on dynamic monitoring of eResid */
         /* --------------------------------------------------------*/

         /* Update the Ritz value and eigenresidual using the */
         /* following recurrences.                            */
      
         Delta = gamma*Delta_prev + eta*rho_prev;
         Beta = Beta_prev - Delta;
         Phi = gamma*gamma*Phi_prev + eta*eta*sigma_prev;
         Psi = gamma*Psi_prev + gamma*Phi_prev;
         Gamma = Gamma_prev + 2.0L*Psi + Phi;

         /* Perform the update: update the eigenvalue and the square of the  */
         /* residual norm.                                                   */
      
         dot_sol = dist_dot(sol, 1, sol, 1, primme);
         eval_updated = shift + (eval - shift + 2*Beta + Gamma)/(1 + dot_sol);
         eres2_updated = (tau*tau)/(1 + dot_sol) + 
            ((eval - shift + Beta)*(eval - shift + Beta))/(1 + dot_sol) - 
            (eval_updated - shift)*(eval_updated - shift);

	 /* If numerical problems, let eres about the same as tau */
	 if (eres2_updated < 0){
            eres_updated = sqrt( (tau*tau)/(1 + dot_sol) );
	 }
	 else 
            eres_updated = sqrt(eres2_updated);

         /* --------------------------------------------------------*/
	 /* Stopping criteria                                       */
         /* --------------------------------------------------------*/

         R = max(0.9878, sqrt(tau/tau_prev))*sqrt(1+dot_sol);
        
	 if ( tau <= R*eres_updated || eres_updated <= tau*R ) {
            if (primme->printLevel >= 5 && primme->procID == 0) {
               fprintf(primme->outputFile, " tau < R eres \n");
            }
	    break;
	 }

	 if (primme->target == primme_smallest && eval_updated > eval_prev) {
            if (primme->printLevel >= 5 && primme->procID == 0) {
               fprintf(primme->outputFile, "eval_updated > eval_prev\n");
            }
	    break;
	 }
	 else if (primme->target == primme_largest && eval_updated < eval_prev){
            if (primme->printLevel >= 5 && primme->procID == 0) {
               fprintf(primme->outputFile, "eval_updated < eval_prev\n");
	    }
	    break;
	 }
	 
         if (eres_updated < ETolerance) {    // tau < LTol has been checked
            if (primme->printLevel >= 5 && primme->procID == 0) {
               fprintf(primme->outputFile, "eres < eresTol %e \n",eres_updated);
            }
            break;
         }

         eval_prev = eval_updated;

         if (primme->printLevel >= 4 && primme->procID == 0) {
            fprintf(primme->outputFile,
           "INN MV %d Sec %e Eval %e Lin|r| %.3e EV|r| %.3e\n", primme->stats.
	    numMatvecs, primme_wTimer(0), eval_updated, tau, eres_updated);
	    fflush(primme->outputFile);
         }

        /* --------------------------------------------------------*/
      } /* End of if adaptive JDQMR section                        */
        /* --------------------------------------------------------*/
      else if (primme->printLevel >= 4 && primme->procID == 0) {
        // Report for non adaptive inner iterations
        fprintf(primme->outputFile,
           "INN MV %d Sec %e Lin|r| %e\n", primme->stats.numMatvecs,
           primme_wTimer(0),tau);
	fflush(primme->outputFile);
      }

      if (numIts < maxIterations) {

	 ret = apply_projected_preconditioner(g, evecs, RprojectorQ, 
	   x, RprojectorX, sizeRprojectorQ, sizeRprojectorX, 
	   xKinvx, UDU, ipivot, w, workSpace, primme);

         if (ret != 0) {
            primme_PushErrorMessage(Primme_inner_solve, 
               Primme_apply_projected_preconditioner, ret, __FILE__, __LINE__, 
               primme);
               ret = APPLYPROJECTEDPRECONDITIONER_FAILURE;
	       break;
         }
         rho = dist_dot(g, 1, w, 1, primme);
         beta = rho/rho_prev;
         Num_scal_dprimme(primme->nLocal, beta, d, 1);
         Num_axpy_dprimme(primme->nLocal, tpone, w, 1, d, 1);
      
         rho_prev = rho; 
         tau_prev = tau;
         Theta_prev = Theta;

         Delta_prev = Delta;
         Beta_prev = Beta;
         Phi_prev = Phi;
         Psi_prev = Psi;
         Gamma_prev = Gamma;
      }

     /* --------------------------------------------------------*/
   } /* End of QMR main while loop                              */
     /* --------------------------------------------------------*/

   *rnorm = eres_updated;
   return 0;
}