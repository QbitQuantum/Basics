void mexFunction
(
    /* === Parameters ======================================================= */

    int nlhs,			/* number of left-hand sides */
    mxArray *plhs [],		/* left-hand side matrices */
    int nrhs,			/* number of right--hand sides */
    const mxArray *prhs []	/* right-hand side matrices */
)
{
    Dmat A;
    DILUPACKparam param;
    mxArray *A_input;
    integer *p, *invq, nB=0;
    double  *prowscale, *pcolscale;
    int     ierr, i,j,k,l;
    size_t  mrows, ncols; 
    mwSize  nnz;
    double  *pr, *D, *A_a;
    mwIndex *A_ia, *A_ja;

    if (nrhs != 1)
       mexErrMsgTxt("One input argument required.");
    else if (nlhs!=2)
       mexErrMsgTxt("Two output arguments are required.");
    else if (!mxIsNumeric(prhs[0]))
       mexErrMsgTxt("First input must be a matrix.");

    /* The first input must be a square matrix.*/
    A_input=(mxArray *)prhs[0];
    mrows = mxGetM(A_input);
    ncols = mxGetN(A_input);
    nnz = mxGetNzmax(A_input);
    if (mrows!=ncols) {
      mexErrMsgTxt("First input must be a square matrix.");
    }
    A_ja         = (mwIndex *)mxGetIr(A_input);
    A_ia         = (mwIndex *)mxGetJc(A_input) ;
    A_a          = (double *) mxGetPr(A_input) ;


    A.nc=A.nr=mrows;
    A.ia=(integer *)MAlloc((size_t)(A.nc+1)*sizeof(integer),"symmwmilupackmetisn");
    A.ja=(integer *)MAlloc((size_t)nnz     *sizeof(integer),"symmwmilupackmetisn");
    A.a =(double *) MAlloc((size_t)nnz     *sizeof(double), "symmwmilupackmetisn");
    A.ia[0]=1;
    for (i = 0 ; i < ncols ; i++) {
        A.ia[i+1]=A.ia[i];
	for (j = A_ia[i] ; j < A_ia[i+1] ; j++) {
  	    /* a_ik */
	    k=A_ja[j];
	    if (k>=i) {
	       l=A.ia[i+1]-1;
	       A.ja[l]=k+1;
	       A.a[l]=A_a[j];
	       A.ia[i+1]=l+2;
	    }
	}
    }

    /* init parameters to their default values */
    DSYMAMGinit(&A,&param);

    p   =(integer *) MAlloc((size_t)A.nc*sizeof(integer),"symmwmilupackmetisn");
    invq=(integer *) MAlloc((size_t)A.nc*sizeof(integer),"symmwmilupackmetisn");
    pcolscale=(double *) MAlloc((size_t)A.nc*sizeof(double),"symmwmilupackmetisn");
    prowscale=pcolscale;
#ifdef _MC64_MATCHING_    
    ierr=DSYMperm_mc64_metis_n(A, prowscale, pcolscale, p, invq, &nB, &param);
#elif defined _PARDISO_MATCHING_
    ierr=DSYMperm_mwm_metis_n(A, prowscale, pcolscale, p, invq, &nB, &param);
#else /* MUMPS matching */
    ierr=DSYMperm_matching_metis_n(A, prowscale, pcolscale, p, invq, &nB, &param);
#endif


    /* Create output vector */
    nlhs=2;
    plhs[0] =mxCreateDoubleMatrix(1,mrows, mxREAL);
    pr = (double *) mxGetPr(plhs[0]);
    for (i=0;i<mrows; i++)
        pr[i]=p[i];


    plhs[1] =mxCreateDoubleMatrix(mrows,1, mxREAL);
    D = (double *) mxGetPr(plhs[1]);
    for (i=0;i<mrows; i++)
        D[i]=pcolscale[i];

    free(p);
    free(invq);
    free(prowscale);
    free(A.ia);
    free(A.ja);
    return;
}