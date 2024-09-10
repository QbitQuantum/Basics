long double SigDig(long double x, size_t n)
{
    long double shift, result;

    if ((n == 0u) || (n > LDBL_DIG))
        result = x;
    else
    {
        --n;
        
#if defined(__DJGPP__) | defined(_MSC_VER)
        shift = pow(10.0L,(double)n - floor(log10(fabs(x))));
#else
        shift = powl(10.0L,(double)n - floorl(log10l(fabsl(x))));
#endif

        result = ToNearest(x * shift) / shift;
    }

    return result;
}