int main() {
    double x = 1.0;
    double y = 1.0;
    int i = 1;
    acosh(x);
    asinh(x);
    atanh(x);
    cbrt(x);
    expm1(x);
    erf(x);
    erfc(x);
    isnan(x);
    j0(x);
    j1(x);
    jn(i,x);
    ilogb(x);
    logb(x);
    log1p(x);
    rint(x);
    y0(x);
    y1(x);
    yn(i,x);
#   ifdef _THREAD_SAFE
    gamma_r(x,&i);
    lgamma_r(x,&i);
#   else
    gamma(x);
    lgamma(x);
#   endif
    hypot(x,y);
    nextafter(x,y);
    remainder(x,y);
    scalb(x,y);
    return 0;
}