void rndit(double *a, double *b, int n)
{
    int i ;

    for (i=0; i<n; ++i) {
        a[i] = nearbyint(b[i]) ;
    }
}