 int ctbcon_(char *norm, char *uplo, char *diag, int *n, 
	int *kd, complex *ab, int *ldab, float *rcond, complex *work, 
	float *rwork, int *info)
{
    /* System generated locals */
    int ab_dim1, ab_offset, i__1;
    float r__1, r__2;

    /* Builtin functions */
    double r_imag(complex *);

    /* Local variables */
    int ix, kase, kase1;
    float scale;
    extern int lsame_(char *, char *);
    int isave[3];
    float anorm;
    int upper;
    extern  int clacn2_(int *, complex *, complex *, float 
	    *, int *, int *);
    float xnorm;
    extern int icamax_(int *, complex *, int *);
    extern double clantb_(char *, char *, char *, int *, int *, 
	    complex *, int *, float *), slamch_(
	    char *);
    extern  int clatbs_(char *, char *, char *, char *, 
	    int *, int *, complex *, int *, complex *, float *, 
	    float *, int *), xerbla_(char *
, int *);
    float ainvnm;
    extern  int csrscl_(int *, float *, complex *, int 
	    *);
    int onenrm;
    char normin[1];
    float smlnum;
    int nounit;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     Modified to call CLACN2 in place of CLACON, 10 Feb 03, SJH. */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  CTBCON estimates the reciprocal of the condition number of a */
/*  triangular band matrix A, in either the 1-norm or the infinity-norm. */

/*  The norm of A is computed and an estimate is obtained for */
/*  norm(inv(A)), then the reciprocal of the condition number is */
/*  computed as */
/*     RCOND = 1 / ( norm(A) * norm(inv(A)) ). */

/*  Arguments */
/*  ========= */

/*  NORM    (input) CHARACTER*1 */
/*          Specifies whether the 1-norm condition number or the */
/*          infinity-norm condition number is required: */
/*          = '1' or 'O':  1-norm; */
/*          = 'I':         Infinity-norm. */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  A is upper triangular; */
/*          = 'L':  A is lower triangular. */

/*  DIAG    (input) CHARACTER*1 */
/*          = 'N':  A is non-unit triangular; */
/*          = 'U':  A is unit triangular. */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  KD      (input) INTEGER */
/*          The number of superdiagonals or subdiagonals of the */
/*          triangular band matrix A.  KD >= 0. */

/*  AB      (input) COMPLEX array, dimension (LDAB,N) */
/*          The upper or lower triangular band matrix A, stored in the */
/*          first kd+1 rows of the array. The j-th column of A is stored */
/*          in the j-th column of the array AB as follows: */
/*          if UPLO = 'U', AB(kd+1+i-j,j) = A(i,j) for MAX(1,j-kd)<=i<=j; */
/*          if UPLO = 'L', AB(1+i-j,j)    = A(i,j) for j<=i<=MIN(n,j+kd). */
/*          If DIAG = 'U', the diagonal elements of A are not referenced */
/*          and are assumed to be 1. */

/*  LDAB    (input) INTEGER */
/*          The leading dimension of the array AB.  LDAB >= KD+1. */

/*  RCOND   (output) REAL */
/*          The reciprocal of the condition number of the matrix A, */
/*          computed as RCOND = 1/(norm(A) * norm(inv(A))). */

/*  WORK    (workspace) COMPLEX array, dimension (2*N) */

/*  RWORK   (workspace) REAL array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Statement Functions .. */
/*     .. */
/*     .. Statement Function definitions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1;
    ab -= ab_offset;
    --work;
    --rwork;

    /* Function Body */
    *info = 0;
    upper = lsame_(uplo, "U");
    onenrm = *(unsigned char *)norm == '1' || lsame_(norm, "O");
    nounit = lsame_(diag, "N");

    if (! onenrm && ! lsame_(norm, "I")) {
	*info = -1;
    } else if (! upper && ! lsame_(uplo, "L")) {
	*info = -2;
    } else if (! nounit && ! lsame_(diag, "U")) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*kd < 0) {
	*info = -5;
    } else if (*ldab < *kd + 1) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CTBCON", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0) {
	*rcond = 1.f;
	return 0;
    }

    *rcond = 0.f;
    smlnum = slamch_("Safe minimum") * (float) MAX(*n,1);

/*     Compute the 1-norm of the triangular matrix A or A'. */

    anorm = clantb_(norm, uplo, diag, n, kd, &ab[ab_offset], ldab, &rwork[1]);

/*     Continue only if ANORM > 0. */

    if (anorm > 0.f) {

/*        Estimate the 1-norm of the inverse of A. */

	ainvnm = 0.f;
	*(unsigned char *)normin = 'N';
	if (onenrm) {
	    kase1 = 1;
	} else {
	    kase1 = 2;
	}
	kase = 0;
L10:
	clacn2_(n, &work[*n + 1], &work[1], &ainvnm, &kase, isave);
	if (kase != 0) {
	    if (kase == kase1) {

/*              Multiply by inv(A). */

		clatbs_(uplo, "No transpose", diag, normin, n, kd, &ab[
			ab_offset], ldab, &work[1], &scale, &rwork[1], info);
	    } else {

/*              Multiply by inv(A'). */

		clatbs_(uplo, "Conjugate transpose", diag, normin, n, kd, &ab[
			ab_offset], ldab, &work[1], &scale, &rwork[1], info);
	    }
	    *(unsigned char *)normin = 'Y';

/*           Multiply by 1/SCALE if doing so will not cause overflow. */

	    if (scale != 1.f) {
		ix = icamax_(n, &work[1], &c__1);
		i__1 = ix;
		xnorm = (r__1 = work[i__1].r, ABS(r__1)) + (r__2 = r_imag(&
			work[ix]), ABS(r__2));
		if (scale < xnorm * smlnum || scale == 0.f) {
		    goto L20;
		}
		csrscl_(n, &scale, &work[1], &c__1);
	    }
	    goto L10;
	}

/*        Compute the estimate of the reciprocal condition number. */

	if (ainvnm != 0.f) {
	    *rcond = 1.f / anorm / ainvnm;
	}
    }

L20:
    return 0;

/*     End of CTBCON */

} /* ctbcon_ */