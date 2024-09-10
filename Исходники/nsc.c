void divarc(real x1, real y1, real z1,
            real x2, real y2, real z2,
            int div1, int div2, real *xr, real *yr, real *zr)
{

    real xd, yd, zd, dd, d1, d2, s, x, y, z;
    real phi, sphi, cphi;

    xd = y1*z2-y2*z1;
    yd = z1*x2-z2*x1;
    zd = x1*y2-x2*y1;
    dd = sqrt(xd*xd+yd*yd+zd*zd);
    if (dd < DP_TOL)
    {
        ERROR("divarc: rotation axis of length %f", dd);
    }

    d1 = x1*x1+y1*y1+z1*z1;
    if (d1 < 0.5)
    {
        ERROR("divarc: vector 1 of sq.length %f", d1);
    }
    d2 = x2*x2+y2*y2+z2*z2;
    if (d2 < 0.5)
    {
        ERROR("divarc: vector 2 of sq.length %f", d2);
    }

    phi  = ASIN(dd/sqrt(d1*d2));
    phi  = phi*((real)div1)/((real)div2);
    sphi = sin(phi); cphi = cos(phi);
    s    = (x1*xd+y1*yd+z1*zd)/dd;

    x   = xd*s*(1.-cphi)/dd + x1 * cphi + (yd*z1-y1*zd)*sphi/dd;
    y   = yd*s*(1.-cphi)/dd + y1 * cphi + (zd*x1-z1*xd)*sphi/dd;
    z   = zd*s*(1.-cphi)/dd + z1 * cphi + (xd*y1-x1*yd)*sphi/dd;
    dd  = sqrt(x*x+y*y+z*z);
    *xr = x/dd; *yr = y/dd; *zr = z/dd;
}