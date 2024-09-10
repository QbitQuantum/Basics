static PetscErrorCode KSPSolve_LSQR(KSP ksp)
{
  PetscErrorCode ierr;
  PetscInt       i,size1,size2;
  PetscScalar    rho,rhobar,phi,phibar,theta,c,s,tmp,tau;
  PetscReal      beta,alpha,rnorm;
  Vec            X,B,V,V1,U,U1,TMP,W,W2,SE,Z = NULL;
  Mat            Amat,Pmat;
  MatStructure   pflag;
  KSP_LSQR       *lsqr = (KSP_LSQR*)ksp->data;
  PetscBool      diagonalscale,nopreconditioner;

  PetscFunctionBegin;
  ierr = PCGetDiagonalScale(ksp->pc,&diagonalscale);CHKERRQ(ierr);
  if (diagonalscale) SETERRQ1(PetscObjectComm((PetscObject)ksp),PETSC_ERR_SUP,"Krylov method %s does not support diagonal scaling",((PetscObject)ksp)->type_name);

  ierr = PCGetOperators(ksp->pc,&Amat,&Pmat,&pflag);CHKERRQ(ierr);
  ierr = PetscObjectTypeCompare((PetscObject)ksp->pc,PCNONE,&nopreconditioner);CHKERRQ(ierr);

  /*  nopreconditioner =PETSC_FALSE; */
  /* Calculate norm of right hand side */
  ierr = VecNorm(ksp->vec_rhs,NORM_2,&lsqr->rhs_norm);CHKERRQ(ierr);

  /* mark norm of matrix with negative number to indicate it has not yet been computed */
  lsqr->anorm = -1.0;

  /* vectors of length m, where system size is mxn */
  B  = ksp->vec_rhs;
  U  = lsqr->vwork_m[0];
  U1 = lsqr->vwork_m[1];

  /* vectors of length n */
  X  = ksp->vec_sol;
  W  = lsqr->vwork_n[0];
  V  = lsqr->vwork_n[1];
  V1 = lsqr->vwork_n[2];
  W2 = lsqr->vwork_n[3];
  if (!nopreconditioner) Z = lsqr->vwork_n[4];

  /* standard error vector */
  SE = lsqr->se;
  if (SE) {
    ierr = VecGetSize(SE,&size1);CHKERRQ(ierr);
    ierr = VecGetSize(X,&size2);CHKERRQ(ierr);
    if (size1 != size2) SETERRQ2(PETSC_COMM_SELF,PETSC_ERR_ARG_SIZ,"Standard error vector (size %d) does not match solution vector (size %d)",size1,size2);
    ierr = VecSet(SE,0.0);CHKERRQ(ierr);
  }

  /* Compute initial residual, temporarily use work vector u */
  if (!ksp->guess_zero) {
    ierr = KSP_MatMult(ksp,Amat,X,U);CHKERRQ(ierr);       /*   u <- b - Ax     */
    ierr = VecAYPX(U,-1.0,B);CHKERRQ(ierr);
  } else {
    ierr = VecCopy(B,U);CHKERRQ(ierr);            /*   u <- b (x is 0) */
  }

  /* Test for nothing to do */
  ierr       = VecNorm(U,NORM_2,&rnorm);CHKERRQ(ierr);
  ierr       = PetscObjectSAWsTakeAccess((PetscObject)ksp);CHKERRQ(ierr);
  ksp->its   = 0;
  ksp->rnorm = rnorm;
  ierr       = PetscObjectSAWsGrantAccess((PetscObject)ksp);CHKERRQ(ierr);
  ierr = KSPLogResidualHistory(ksp,rnorm);CHKERRQ(ierr);
  ierr = KSPMonitor(ksp,0,rnorm);CHKERRQ(ierr);
  ierr = (*ksp->converged)(ksp,0,rnorm,&ksp->reason,ksp->cnvP);CHKERRQ(ierr);
  if (ksp->reason) PetscFunctionReturn(0);

  beta = rnorm;
  ierr = VecScale(U,1.0/beta);CHKERRQ(ierr);
  ierr = KSP_MatMultTranspose(ksp,Amat,U,V);CHKERRQ(ierr);
  if (nopreconditioner) {
    ierr = VecNorm(V,NORM_2,&alpha);CHKERRQ(ierr);
  } else {
    ierr = PCApply(ksp->pc,V,Z);CHKERRQ(ierr);
    ierr = VecDotRealPart(V,Z,&alpha);CHKERRQ(ierr);
    if (alpha <= 0.0) {
      ksp->reason = KSP_DIVERGED_BREAKDOWN;
      PetscFunctionReturn(0);
    }
    alpha = PetscSqrtReal(alpha);
    ierr  = VecScale(Z,1.0/alpha);CHKERRQ(ierr);
  }
  ierr = VecScale(V,1.0/alpha);CHKERRQ(ierr);

  if (nopreconditioner) {
    ierr = VecCopy(V,W);CHKERRQ(ierr);
  } else {
    ierr = VecCopy(Z,W);CHKERRQ(ierr);
  }

  lsqr->arnorm = alpha * beta;
  phibar       = beta;
  rhobar       = alpha;
  i            = 0;
  do {
    if (nopreconditioner) {
      ierr = KSP_MatMult(ksp,Amat,V,U1);CHKERRQ(ierr);
    } else {
      ierr = KSP_MatMult(ksp,Amat,Z,U1);CHKERRQ(ierr);
    }
    ierr = VecAXPY(U1,-alpha,U);CHKERRQ(ierr);
    ierr = VecNorm(U1,NORM_2,&beta);CHKERRQ(ierr);
    if (beta == 0.0) {
      ksp->reason = KSP_DIVERGED_BREAKDOWN;
      break;
    }
    ierr = VecScale(U1,1.0/beta);CHKERRQ(ierr);

    ierr = KSP_MatMultTranspose(ksp,Amat,U1,V1);CHKERRQ(ierr);
    ierr = VecAXPY(V1,-beta,V);CHKERRQ(ierr);
    if (nopreconditioner) {
      ierr = VecNorm(V1,NORM_2,&alpha);CHKERRQ(ierr);
    } else {
      ierr = PCApply(ksp->pc,V1,Z);CHKERRQ(ierr);
      ierr = VecDotRealPart(V1,Z,&alpha);CHKERRQ(ierr);
      if (alpha <= 0.0) {
        ksp->reason = KSP_DIVERGED_BREAKDOWN;
        break;
      }
      alpha = PetscSqrtReal(alpha);
      ierr  = VecScale(Z,1.0/alpha);CHKERRQ(ierr);
    }
    ierr   = VecScale(V1,1.0/alpha);CHKERRQ(ierr);
    rho    = PetscSqrtScalar(rhobar*rhobar + beta*beta);
    c      = rhobar / rho;
    s      = beta / rho;
    theta  = s * alpha;
    rhobar = -c * alpha;
    phi    = c * phibar;
    phibar = s * phibar;
    tau    = s * phi;

    ierr = VecAXPY(X,phi/rho,W);CHKERRQ(ierr);  /*    x <- x + (phi/rho) w   */

    if (SE) {
      ierr = VecCopy(W,W2);CHKERRQ(ierr);
      ierr = VecSquare(W2);CHKERRQ(ierr);
      ierr = VecScale(W2,1.0/(rho*rho));CHKERRQ(ierr);
      ierr = VecAXPY(SE, 1.0, W2);CHKERRQ(ierr); /* SE <- SE + (w^2/rho^2) */
    }
    if (nopreconditioner) {
      ierr = VecAYPX(W,-theta/rho,V1);CHKERRQ(ierr);  /* w <- v - (theta/rho) w */
    } else {
      ierr = VecAYPX(W,-theta/rho,Z);CHKERRQ(ierr);   /* w <- z - (theta/rho) w */
    }

    lsqr->arnorm = alpha*PetscAbsScalar(tau);
    rnorm        = PetscRealPart(phibar);

    ierr = PetscObjectSAWsTakeAccess((PetscObject)ksp);CHKERRQ(ierr);
    ksp->its++;
    ksp->rnorm = rnorm;
    ierr       = PetscObjectSAWsGrantAccess((PetscObject)ksp);CHKERRQ(ierr);
    ierr = KSPLogResidualHistory(ksp,rnorm);CHKERRQ(ierr);
    ierr = KSPMonitor(ksp,i+1,rnorm);CHKERRQ(ierr);
    ierr = (*ksp->converged)(ksp,i+1,rnorm,&ksp->reason,ksp->cnvP);CHKERRQ(ierr);
    if (ksp->reason) break;
    SWAP(U1,U,TMP);
    SWAP(V1,V,TMP);

    i++;
  } while (i<ksp->max_it);
  if (i >= ksp->max_it && !ksp->reason) ksp->reason = KSP_DIVERGED_ITS;

  /* Finish off the standard error estimates */
  if (SE) {
    tmp  = 1.0;
    ierr = MatGetSize(Amat,&size1,&size2);CHKERRQ(ierr);
    if (size1 > size2) tmp = size1 - size2;
    tmp  = rnorm / PetscSqrtScalar(tmp);
    ierr = VecSqrtAbs(SE);CHKERRQ(ierr);
    ierr = VecScale(SE,tmp);CHKERRQ(ierr);
  }
  PetscFunctionReturn(0);
}