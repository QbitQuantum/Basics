long double
sinhl(long double x)
{
    long double	r, t;

    if (!finitel(x))
        return (x + x);	/* x is INF or NaN */
    r = fabsl(x);
    if (r < lnovft) {
        t = expm1l(r);
        r = copysignl((t + t / (one + t)) * half, x);
    } else {
        r = copysignl(expl((r - lnovft) - lnovlo), x);
        r = scalbnl(r, 16383);
    }
    return (r);
}