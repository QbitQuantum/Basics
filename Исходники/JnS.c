void Jade (
	     double *B, /* Output. Separating matrix. nbc*nbc */
	     double *X, /* Input.  Data set nbc x nbs */
	     int nbc,   /* Input.  Number of sensors  */
	     int nbs    /* Input.  Number of samples  */
	     )
{
  double threshold_JD = RELATIVE_JD_THRESHOLD / sqrt((double)nbs) ;
  int rots = 1 ;
  double *Transf  = (double *) calloc(nbc*nbc,         sizeof(double)) ; 
  double *CumTens = (double *) calloc(nbc*nbc*nbc*nbc, sizeof(double)) ; 
  if ( Transf == NULL || CumTens == NULL ) OutOfMemory() ;

  /* Init */
  Message0(2, "Init...\n") ;
  Identity(B, nbc); 

  MeanRemoval(X, nbc, nbs)  ; 
printf ("mean\n");

  PrintMat (X, nbc, nbs) ;
printf ("\n");

Message0(2, "Whitening...\n") ;	
  ComputeWhitener(Transf, X, nbc, nbs)  ; 
	
  printf ("Whitener:\n");
  PrintMat (Transf, nbc, nbc) ;
printf ("\n");

  Transform (X, Transf,          nbc, nbs) ;
printf ("Trans X\n");
PrintMat (X, nbc, nbs) ;
printf ("\n");

  Transform (B, Transf,          nbc, nbc) ;


  Message0(2, "Estimating the cumulant tensor...\n") ;
  EstCumTens (CumTens, X,      nbc, nbs) ;

  printf ("cum tens \n");
  PrintMat (CumTens, nbc*nbc, nbc*nbc) ;
	printf ("\n");

  Message0(2, "Joint diagonalization...\n") ;
  rots = JointDiago (CumTens, Transf,  nbc, nbc*nbc, threshold_JD) ;
  MessageI(3, "Total number of plane rotations: %6i.\n", rots) ;
  MessageF(3, "Size of the total rotation: %10.7e\n", NonIdentity(Transf,nbc) )  ;
  
  printf ("Trans mat\n");
  PrintMat (Transf, nbc, nbc) ;
  printf ("\n");

  Message0(2, "Updating...\n") ;
  Transform  (X, Transf,        nbc, nbs ) ;
  Transform  (B, Transf,        nbc, nbc ) ;

  printf ("resultant \n");
  PrintMat (X, nbc, nbs) ;
  printf ("\n");

  printf ("estimated mix \n");
  PrintMat (B, nbc, nbc) ;
  printf ("\n");

  free(Transf) ; 
  free(CumTens) ;
}