kiss_fft_cpx sf_ctanhf(kiss_fft_cpx z)
/*< complex hyperbolic tangent >*/
{
    float x, y, d;

    x = z.r;
    y = z.i;

    d = coshf(2*x) + cosf(2*y);
    z.r = sinhf(2*x)/ d;
    z.i = sinf (2*y)/ d;

    return z;
}