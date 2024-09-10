static double jinc(params *p, double x)
{
    if (fabs(x) < 1e-8)
        return 1.0;
    double pix = M_PI * x;
    return 2.0 * j1(pix) / pix;
}