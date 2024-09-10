void critfunc(double *grad, int *nPar, int *nD, double *probs, int *M,
              double *design, double *n2, double *nold,
              double *A, double *tol, double *MEDgrad, int *type,
	      int *stand, double *res){
  // grad - contains gradient vectors (4 cells reserved for each model)
  // nPar - number of parameters (dim A)
  // nD - number of dose-levels
  // design - design
  // type - 1: MED, 2: Dopt, 3: MED&Dopt
  int m,incgrad=0,incb=0;
  double resM=0,resD=0,fracp=0;
  // variables for SVD decomposition, initialize to max possible dimension
  double work[30]={0.0};
  double s[4]={0.0}; 
  double VT[16]={0.0};
  double U[16]={0.0};
  *res = 0.0;

  // calculate weight vector
  getAllocs(design, n2, nold, nD);
  for(m=0;m<*M;m++){
    if(m > 0){
      incgrad+=*nD*nPar[m-1];
      incb+=nPar[m-1];
    }
    setzero(A, 16);resM = 0.0;
    // calulate matrix 
    calcMat(grad, &nPar[m], design, nD, A, &incgrad);
    // calculate det and/or  MP-Inverse 
    calcDetGinv(A, &nPar[m], work, s, VT, U,
		tol, type, &resD);
    if(*type == 1){  // calculate quadratic form (for MED designs)
      calcQuadform(MEDgrad, A, &nPar[m], &resM, &incb);
      *res += probs[m]*log(resM);
    }
    if(*type == 2){
      if(*stand == 1){
	fracp = (double) nPar[m];
	*res += probs[m]*(-log(resD)/fracp);	
      } else {
	*res += probs[m]*(-log(resD));
      }
    }
    if(*type == 3){  // calculate quadratic form (for MED designs)
      calcQuadform(MEDgrad, A, &nPar[m], &resM, &incb);
      if(*stand == 1){
	fracp = (double) nPar[m];
	*res += probs[m]*(-0.5*log(resD)/fracp+0.5*log(resM));
      } else {
	*res += probs[m]*(-0.5*log(resD)+0.5*log(resM));
      }
    }
  }
}