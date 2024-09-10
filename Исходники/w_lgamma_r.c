double
__lgamma_r(double x, int *signgamp)
{
    double y = __ieee754_lgamma_r(x,signgamp);
    if(__builtin_expect(!__finite(y), 0)
            && __finite(x) && _LIB_VERSION != _IEEE_)
        return __kernel_standard(x, x,
                                 __floor(x)==x&&x<=0.0
                                 ? 15 /* lgamma pole */
                                 : 14); /* lgamma overflow */

    return y;
}