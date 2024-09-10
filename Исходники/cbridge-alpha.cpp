double Bridge:: find_zeta_max(const double theta)
{
    // a good value
    double zeta_lo = 0.0;
    if( find_alpha(theta, zeta_lo, NULL) < 0 )
    {
        throw exception("Cannot find alpha for zeta=0");
    }

    // a bad balue
    double zeta_up = 1.0;
    while(find_alpha(theta,zeta_up,NULL)>=0)
    {
        zeta_lo = zeta_up;
        zeta_up += 1.0;
    }
    std::cerr << "Looking up between " << zeta_lo << " and " << zeta_up << std::endl;
    const double zeta_ftol = numeric<double>::sqrt_ftol;
    while( Fabs(zeta_up-zeta_lo) >= zeta_ftol * ( Fabs(zeta_lo) + Fabs(zeta_up) ) )
    {
        const double zeta_mid = 0.5*(zeta_lo+zeta_up);
        if(find_alpha(theta,zeta_mid,NULL) < 0 )
        {
            zeta_up = zeta_mid;
        }
        else
        {
            zeta_lo = zeta_mid;
        }
    }

    // highest good value
    return zeta_lo;
}