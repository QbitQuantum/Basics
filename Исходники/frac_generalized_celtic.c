depth_t frac_generalized_celtic(depth_t depth,
                                long double wim,     long double wre,
                                long double c_im,    long double c_re,
                                long double wim2,    long double wre2  )
{
    depth_t wz;
    for (wz = 1; wz <= depth; ++wz)
    {
        wim = 2.0 * wre * wim + c_im;
        wre = fabsl(wre2 - wim2) + c_re;
        wim2 = wim * wim;
        wre2 = wre * wre;

        if (wim2 + wre2 > 4.0F)
            return wz;
    }
    return 0;
}