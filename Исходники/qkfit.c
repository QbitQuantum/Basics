/* Subroutine */ 
int qkfit(doublereal *umat, doublereal *rtsum, doublereal *r, integer *entry_) {

    /* Initialized data */

    static doublereal eps = 1e-5;
    static doublereal pi = 3.14159265358979;
    static doublereal one = 1.;
    static doublereal two = 2.;
    static doublereal three = 3.;
    static doublereal half = .5;
    static doublereal third = .333333333;
    static doublereal forthr = 1.333333333;
    static struct {
       doublereal fill_1[1];
       doublereal e_2[2];
       doublereal fill_3[2];
       doublereal e_4;
       doublereal fill_5[3];
	} equiv_6 = { {0}, {0.0}, {0.0}, 0, {0.0} };


    /* System generated locals */
    integer i_1;
    static doublereal equiv_7[9];

    /* Builtin functions */
    double sqrt(), d_sign(), atan(), cos();

    /* Local variables */
    static doublereal diff;
    static integer isig;
    static doublereal detu, root[3];
#define a ((doublereal *)&equiv_6)
#define b (equiv_7)
    static integer i, j, k;
    static doublereal s, t;
    extern /* Subroutine */ int eigen_();
    static doublereal digav, theta, argsq, b1, b2;
    extern /* Subroutine */ int esort_();
    static doublereal cos3th, cc, b13, dd, b23;
    static integer ia;
    static doublereal b33, qq, rt;
#define usqmat ((doublereal *)&equiv_6)
#define aam ((doublereal *)&equiv_6)
#define bam ((doublereal *)&equiv_6 + 4)
#define cam ((doublereal *)&equiv_6 + 8)
#define fam ((doublereal *)&equiv_6 + 7)
#define gam ((doublereal *)&equiv_6 + 6)
#define ham ((doublereal *)&equiv_6 + 3)
    static doublereal du11, du21, du31;
#define utr (equiv_7)





    /* Parameter adjustments */
    r -= 4;
    umat -= 4;

    /* Function Body */
    isig = 1;
    if (*entry_ == 1) {
	goto L200;
    }
/*     CALC DET OF UMAT */

    du11 = umat[8] * umat[12] - umat[11] * umat[9];
    du21 = umat[11] * umat[6] - umat[5] * umat[12];
    du31 = umat[5] * umat[9] - umat[8] * umat[6];
    detu = umat[4] * du11 + umat[7] * du21 + umat[10] * du31;
    if (detu < 0.) {
	isig = -1;
    }

/*     FORM USQMAT AS POSITIVE SEMI DEFINITE MATRIX */

    for (j = 1; j <= 3; ++j) {
	i_1 = j;
	for (i = 1; i <= i_1; ++i) {
	    usqmat[i + j * 3 - 4] = umat[i * 3 + 1] * umat[j * 3 + 1] + umat[
		    i * 3 + 2] * umat[j * 3 + 2] + umat[i * 3 + 3] * umat[j * 
		    3 + 3];
/* L105: */
	}
/* L110: */
    }
/* %    WRITE(6,999) USQMAT */

/*     REDUCE AVG OF DIAGONAL TERMS TO ZERO */

    digav = (*aam + *bam + *cam) * third;
/* %    WRITE(6,999) DIGAV */
    *aam -= digav;
    *bam -= digav;
    *cam -= digav;

/*     SETUP COEFFS OF SECULAR EQUATION OF MATRIX WITH TRACE ZERO */

    cc = *fam * *fam + *gam * *gam + *ham * *ham - *aam * *bam - *bam * *cam 
	    - *cam * *aam;
    dd = *aam * *bam * *cam + two * (*fam * *gam * *ham) - *aam * *fam * *fam 
	    - *bam * *gam * *gam - *cam * *ham * *ham;

/*     THE SECULAR EQN IS Y**3-CC*Y-DD=0  AND DD IS DET(USQMAT) */
/*     REDUCE THIS TO THE FORM COS**3-(3/4)COS- */
/*     (1/4)COS3THETA = 0 */
/*     WITH SOLUTIONS COSTHETA.  SO Y=QQ*COSTHETA */

    if (cc <= eps) {
	goto L115;
    }
    qq = sqrt(forthr * cc);
    cos3th = three * dd / (cc * qq);
    if (abs(cos3th) > one) {
/*	cos3th = d_sign(&one, &cos3th);  */
/*      Change suggested by Andrew Torda with many thanks, etc. eliminates the need for the FORTRAN libraries */
	cos3th = (cos3th > 0 ? one:-one); 

    }

/*     FUNCTION ARCOS */

    if (cos3th != 0.) {
	goto L1200;
    }
/* L1100: */
    theta = (float)1.570796327;
    goto L1400;
L1200:
    argsq = cos3th * cos3th;
    theta = atan(sqrt((float)1. - argsq) / cos3th);
    if (cos3th < 0.) {
	theta = pi - theta;
    }
L1400:

/*     ROOTS IN ORDER OF SIZE GO 1,2,3 1 LARGEST */

    theta *= third;
    root[0] = qq * cos(theta);
    diff = half * sqrt(three * (qq * qq - root[0] * root[0]));
    root[1] = -root[0] * half + diff;
    root[2] = -root[0] * half - diff;
    goto L120;
L115:

/*     SPECIAL FOR TRIPLY DEGENERATE */

    root[0] = (float)0.;
    root[1] = (float)0.;
    root[2] = (float)0.;
L120:
/*     ADD ON DIGAV AND TAKE SQRT */
    for (j = 1; j <= 3; ++j) {
	rt = root[j - 1] + digav;
	if (rt < eps) {
	    rt = (float)0.;
	}
	root[j - 1] = sqrt(rt);
/* L125: */
    }
/* %    WRITE(6,999) ROOT */
/*     IF DETU IS <0 CHANGE SIGN OF ROOT(3) */
    if (isig == -1) {
	root[2] = -root[2];
    }
    *rtsum = root[0] + root[1] + root[2];
/* %    WRITE(6,999) RTSUM */
    return 0;

/*     THIS IS THE FANCY PART */

L200:

/*     FORM USQ = (UT).U    (IN UPPER TRIANGULAR SYMMETRIC STORAGE MODE) 
*/

    for (i = 1; i <= 3; ++i) {
	for (j = i; j <= 3; ++j) {
/* SMJS Changed to be like Robs version */
	    t = (doublereal)0.;
	    for (k = 1; k <= 3; ++k) {
		t += umat[k + i * 3] * umat[k + j * 3];
/* L210: */
	    }
	    ia = i + (j * j - j) / 2;
	    utr[ia - 1] = t;
/* L220: */
	}
    }
/* %    WRITE(6,999) UTR */

/*     CALCULATE EIGENVALUES AND VECTORS */

    eigen_(utr, a, &c__3, &c__0);
    esort_(utr, a, &c__3, &c__0);
/* %    WRITE(6,999) UTR */

    root[0] = utr[0];
    root[1] = utr[2];
    root[2] = utr[5];
/* %    WRITE(6,999) ROOT */
/* %    WRITE(6,999) A */

/*     SET A3 = A1 CROSS A2 */
/*     ROOTS ARE IN ORDER R(1) >= R(2) >= R(3) >= 0 */

    a[6] = a[1] * a[5] - a[2] * a[4];
    a[7] = a[2] * a[3] - a[0] * a[5];
    a[8] = a[0] * a[4] - a[1] * a[3];
/* %    WRITE(6,999) A */

/*     VECTOR SET B=U.A */

    for (i = 1; i <= 3; ++i) {
	for (j = 1; j <= 3; ++j) {
/* SMJS Changed to be like Robs version */
	    t = (doublereal)0.;
	    for (k = 1; k <= 3; ++k) {
/* L230: */
		t += umat[j + k * 3] * a[k + i * 3 - 4];
	    }
	    b[j + i * 3 - 4] = t;
/* L240: */
	}
    }

/*      NORMALIZE B1 AND B2 AND CALCULATE B3 = B1 CROSS B2 */

    b1 = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);
    b2 = sqrt(b[3] * b[3] + b[4] * b[4] + b[5] * b[5]);
    for (i = 1; i <= 3; ++i) {
	b[i - 1] /= b1;
/* L250: */
	b[i + 2] /= b2;
    }

/*      CHECK FOR LEFT HANDED ROTATION */

    b13 = b[1] * b[5] - b[2] * b[4];
    b23 = b[2] * b[3] - b[0] * b[5];
    b33 = b[0] * b[4] - b[1] * b[3];

    s = b13 * b[6] + b23 * b[7] + b33 * b[8];
    if (s < 0.) {
	isig = -1;
    }
    b[6] = b13;
    b[7] = b23;
    b[8] = b33;
/* %    WRITE(6,999) B */

/*     CALCULATE ROTATION MATRIX R */

    for (i = 1; i <= 3; ++i) {
	for (j = 1; j <= 3; ++j) {
/* SMJS Changed to be like Robs version */
	    t = (doublereal)0.;
	    for (k = 1; k <= 3; ++k) {
/* L260: */
		t += b[i + k * 3 - 4] * a[j + k * 3 - 4];
	    }
	    r[i + j * 3] = t;
/* L270: */
	}
    }

/*     RMS ERROR */

    for (i = 1; i <= 3; ++i) {
	if (root[i - 1] < 0.) {
	    root[i - 1] = (float)0.;
	}
	root[i - 1] = sqrt(root[i - 1]);
/* L280: */
    }

/*     CHANGE SIGN OF EVAL #3 IF LEFT HANDED */

    if (isig < 0) {
	root[2] = -root[2];
    }
    *rtsum = root[2] + root[1] + root[0];
    return 0;
} /* qkfit_ */