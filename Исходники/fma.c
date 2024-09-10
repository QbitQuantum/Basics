_WMRTLINK double fma(double a, double b, double c)
{
long double product, res;

    if(__math_errhandling_flag != 0) {
        if((a==0.0 && isinf(b)) || (b==0.0 && isinf(a))) {
            __reporterror(DOMAIN, __func__, a, b, NAN);
            return NAN;
        }
    }
    
    /* Not strictly an error condition, but a predefined result */
    if(isnan(a) || isnan(b) || isnan(c))
        return NAN;
    
    /* Check product versus c for error handling */
    product = ((long double)a)*((long double)b);
    
    if(isinf(product) && isinf(c) && _FLSign(product) != _FDSign(c)) {
        if(__math_errhandling_flag != 0)
            __reporterror(DOMAIN, __func__, a, b, NAN);
        return NAN;
    }
    
    res = product + (long double)c;
    
    /* If our result is the same as either the product or the additive
     * argument and neither was zero, we've experienced catastrophic
     * cancelation.  We should report a partial loss of significance.
     */
    if(__math_errhandling_flag != 0 && 
       ((res == product && product != 0.0) || 
        (res == (long double)c && c != 0.0)))
    {
        __reporterror(PLOSS, __func__, a, b, (double)res);
    }
    
    return (double)res;
}