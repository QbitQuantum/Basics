double ks_test::ks_cdf(double z)
{
    // CDF of the Kolmogorov-Smirnov distribution.
    using std::exp; using std::pow; using std::sqrt;
    if(z < 0.0)
    {
        throw("z must be non-negative in ks_cdf in ks_test.");
    }
    else if(z == 0.0)
    {
        return 0.0;
    }
    else if(z < 1.18)
    {
        double x = 1.23370055013616983/square(z);
        double y = exp(-x);
        return 2.25675833419102515*sqrt(x)*
            (y + pow(y,9) + pow(y,25) + pow(y,49));
    }
    else
    {
        double y = exp(-2.0*square(z));
        return 1.0 - 2.0*(y - pow(y,4) + pow(y,9));
    }
}