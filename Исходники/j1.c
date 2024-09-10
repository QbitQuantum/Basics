double
y1(double arg)
{
    double xsq, n, d, x;
    int i;

    errno = 0;
    x = arg;
    if(x <= 0) {
        errno = EDOM;
        return -HUGE_VAL;
    }
    if(x > 8) {
        asympt(x);
        n = x - 3*pio4;
        return sqrt(tpi/x)*(pzero*sin(n) + qzero*cos(n));
    }
    xsq = x*x;
    for(n=0,d=0,i=9; i>=0; i--) {
        n = n*xsq + p4[i];
        d = d*xsq + q4[i];
    }
    return x*n/d + tpi*(j1(x)*log(x)-1/x);
}