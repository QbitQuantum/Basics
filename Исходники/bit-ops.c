/*
	bitwise complement for use with .Call to bitFlip masked to bitWidth
*/
SEXP bitFlip(SEXP a, SEXP bitWidth )
{
    PROTECT (a = AS_NUMERIC(a) ) ;
    PROTECT (bitWidth = AS_INTEGER(bitWidth) ) ;
    int n = LENGTH(a);
    int *xbitWidth = INTEGER_POINTER(bitWidth);
    double *xa  = NUMERIC_POINTER(a);
    unsigned int mask = ( unsigned int ) -1 >> (32 - *xbitWidth);
    SEXP aflip = PROTECT(NEW_NUMERIC(n));
    double *xaflip = NUMERIC_POINTER(aflip);

    for (int i=0; i<n; i++ ) {
	if ( !R_FINITE(xa[i]) || logb(xa[i])>31 )
	    xaflip[i]=NA_REAL ;
	else {
	    // in case of a negative, cast twice;
	    unsigned int tmp = xa[i] < 0 ? (int) xa[i] : (unsigned) xa[i];
	    xaflip[i]=(double) ( ~tmp & mask ) ;
	}
    }
    UNPROTECT(3) ;
    return (aflip) ;
}