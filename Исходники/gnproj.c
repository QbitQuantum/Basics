void gnomic_geod( GnomicProjection *gp, double ce, double cn, double *lon, double *lat)
{

    double psi, u, a1, a2, a3, a4, root, dlam, csth, snth;

    ce -= gp->fe;
    cn -= gp->fn;

    if( ce == 0.0 && cn == 0.0 )
    {
        *lat = gp->orglat;
        *lon = gp->orglon;
        return;
    }

    csth=_hypot(cn,ce);
    snth=cn/csth;
    csth=ce/csth;

    if( ce == 0.0 )
    {
        psi=atan(cn/(gp->a*snth));
    }
    else
    {
        psi=atan(ce/(gp->a*csth));
    }

    u=sin(psi);
    a4=cos(psi);

    a1 = a4*a4;

    a2=gp->csolt*gp->csolt * (csth*csth * u*u  -  1.0);

    a3 = gp->snolt*gp->snolt*a1;

    a4 *= gp->snolt;

    u *= csth;

    root=sqrt(a3-a2-a1);

    if( cn > 0.0 )
    {
        *lat = asin( a4 + root );
    }
    else
    {
        *lat = asin( a4 - root );
    }

    dlam = asin(u/cos(*lat));
    dlam += gp->orglon;
    while( dlam > PI ) dlam -= TWOPI;
    while( dlam < -PI ) dlam += TWOPI;

    *lon = dlam;
}