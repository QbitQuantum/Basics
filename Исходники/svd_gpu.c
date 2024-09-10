void svd_gpu(int m, int n, double* A,double * sigma, double * U, double* V){
  /**********************************************
   * Description: Function call that performs an SVD on the matrix A.
   *
   *  Author: Steven Delong
   * 
   * inputs:
   *         A - m x n matrix, stored in column-major order.
   *	     m - number of rows of A
   *	     n - number of columns of A
   *
   * Outputs:
   *        Uout - left singular vectors of A
   *        Vout - right singular vectors of A
   *        sigma - singular values of A, length min(m,n)
   *
   ***********************************************************/
  //declare variables used for timing.
  timestamp_type time1, time2;
  double elapsed, flops;

  // figure out minimum dimension
  int mn = (m >= n) ? n : m;
  int len_beta = (m >= n) ? n-1 : m;

  // sizes to double for flop calcs
  double dmn = (double) mn;
  double dm = (double) m;
  double dn = (double) n;

  // allocate space for intermediate values
  double * AT = (double *) malloc(sizeof(double) * m *n);
  if(!AT) { fprintf(stderr,"in main: failed to allocate AT\n"); abort();}
  double * alpha = (double *) malloc(sizeof(double) *mn);
  if(!alpha) { fprintf(stderr,"in main: failed to allocate alpha\n"); abort();}

  double *beta = (double *) malloc(sizeof(double) *len_beta);
  if(!beta) { fprintf(stderr,"in main: failed to allocate beta\n"); abort();}
    

  double *X = (double *) malloc(sizeof(double) *mn*(len_beta + 1));
  if(!X) { fprintf(stderr,"in main: failed to allocate X\n"); abort();}
  double *Y = (double *) malloc(sizeof(double) *mn*mn);
  if(!Y) { fprintf(stderr,"in main: failed to allocate Y\n"); abort();}


  // bidiagonalize
  bidiag_par(m,n,A,alpha,beta);

  //transpose householder reflectors for applying to X later
  transpose(m,n,A,AT);
   
  //get singular values
  GetSingularValues_Parallel( mn , alpha, beta, sigma);


  // calculate right singular vectors
  CalcRightSingularVectors(mn,len_beta + 1,alpha,beta,sigma,X);
	
  // get left singular vectors
  RighttoLeftSingularVectors(mn,len_beta + 1,alpha,beta,sigma,X,Y);


  // apply householder reflectors to X,Y to get U,V
#pragma omp parallel for default(shared) firstprivate(A)
  for(int i = 0; i < mn; i++){
      multU(m,n,i,A,Y,U + i*m);
      multV(m,n,i,AT,X,V + i*n);
  }


  // free malloc'd intermediates 
  free(AT);
  free(alpha);
  free(beta);
  free(X);
  free(Y);

}