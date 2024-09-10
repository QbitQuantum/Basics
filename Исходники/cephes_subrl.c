void
_cchshl(long double x, long double *c, long double *s)
{
    long double e, ei;

    if (fabsl(x) <= 0.5L) {
        *c = coshl(x);
        *s = sinhl(x);
    } else {
        e = expl(x);
        ei = 0.5L / e;
        e = 0.5L * e;
        *s = e - ei;
        *c = e + ei;
    }
}