long double mjd_to_gmstl(long double utc_in_mjd, long double delta_ut)
{
    long double ts = utc_in_mjd + delta_ut / SEC_IN_DAY;
    long double ts_trunc = truncl(ts);
    long double s = ts - ts_trunc;
    long double tu = (truncl(ts) - MJD2000) / JULIAN_C;
    long double s0 = 1.753368559233266L + (628.3319706888409L
                                        + (6.770713944903336e-06L - 4.508767234318685e-10L*tu)*tu)*tu;
    long double freq = 1.002737909350795L + (5.900575455674703e-11L - 5.893984333409384e-15L*tu)*tu;

    s0 += freq*s*PI2;
    long double r = s0 / PI2;
    long double i = truncl(r);

    long double gmst = s0 - PI2*i;
    if (gmst < 0)
    {
        gmst += PI2;
    }

    return gmst;
}