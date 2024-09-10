double
__asinh (double x)
{
    double w;
    int32_t hx, ix;
    GET_HIGH_WORD (hx, x);
    ix = hx & 0x7fffffff;
    if (__glibc_unlikely (ix < 0x3e300000))                  /* |x|<2**-28 */
    {
        if (huge + x > one)
            return x;                       /* return x inexact except 0 */
    }
    if (__glibc_unlikely (ix > 0x41b00000))                  /* |x| > 2**28 */
    {
        if (ix >= 0x7ff00000)
            return x + x;                           /* x is inf or NaN */
        w = __ieee754_log (fabs (x)) + ln2;
    }
    else
    {
        double xa = fabs (x);
        if (ix > 0x40000000)              /* 2**28 > |x| > 2.0 */
        {
            w = __ieee754_log (2.0 * xa + one / (__ieee754_sqrt (xa * xa + one) +
                                                 xa));
        }
        else                      /* 2.0 > |x| > 2**-28 */
        {
            double t = xa * xa;
            w = __log1p (xa + t / (one + __ieee754_sqrt (one + t)));
        }
    }
    return __copysign (w, x);
}