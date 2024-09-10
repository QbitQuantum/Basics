inline void inv_gauss(GAUSS const& en, T& lam, T& phi)
{
    lam /= en.C;
    const double num = pow(tan(0.5 * phi + FORTPI) / en.K, 1.0 / en.C);

    int i = 0;
    for (i = MAX_ITER; i; --i)
    {
        const double elp_phi = 2.0 * atan(num * srat(en.e * sin(phi), - 0.5 * en.e)) - HALFPI;

        if (geometry::math::abs(elp_phi - phi) < DEL_TOL)
        {
            break;
        }
        phi = elp_phi;
    }

    /* convergence failed */
    if (!i)
    {
        throw proj_exception(-17);
    }
}