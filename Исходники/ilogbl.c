int ilogbl(long double x) {
    PRAGMA_STDC_FENV_ACCESS_ON
    union ldshape u = {x};
    int e = u.i.se & 0x7fff;

    if (!e) {
        if (x == 0) {
            FORCE_EVAL(0 / 0.0f);
            return FP_ILOGB0;
        }
        /* subnormal x */
        x *= 0x1p120;
        return ilogbl(x) - 120;
    }
    if (e == 0x7fff) {
        FORCE_EVAL(0 / 0.0f);
        u.i.se = 0;
        return u.f ? FP_ILOGBNAN : INT_MAX;
    }
    return e - 0x3fff;
}