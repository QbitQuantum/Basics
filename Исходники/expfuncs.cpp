ssfloat ExpMgr::gnoise(ssfloat x, ssfloat y, ssfloat z)
{
    int ix, iy, iz;
    ssfloat fx0, fx1, fy0, fy1, fz0, fz1;
    ssfloat wx, wy, wz;
    ssfloat vx0, vx1, vy0, vy1, vz0, vz1;
    static int initialized = 0;

    if (!initialized) {
        gradientTabInit(665);
        initialized = 1;
    }

    ix = FLOOR(x);
    fx0 = x - ix;
    fx1 = fx0 - 1;
    wx = SMOOTHSTEP(fx0);

    iy = FLOOR(y);
    fy0 = y - iy;
    fy1 = fy0 - 1;
    wy = SMOOTHSTEP(fy0);

    iz = FLOOR(z);
    fz0 = z - iz;
    fz1 = fz0 - 1;
    wz = SMOOTHSTEP(fz0);

    vx0 = glattice(ix,iy,iz,fx0,fy0,fz0);
    vx1 = glattice(ix+1,iy,iz,fx1,fy0,fz0);
    vy0 = LERP(wx, vx0, vx1);
    vx0 = glattice(ix,iy+1,iz,fx0,fy1,fz0);
    vx1 = glattice(ix+1,iy+1,iz,fx1,fy1,fz0);
    vy1 = LERP(wx, vx0, vx1);
    vz0 = LERP(wy, vy0, vy1);

    vx0 = glattice(ix,iy,iz+1,fx0,fy0,fz1);
    vx1 = glattice(ix+1,iy,iz+1,fx1,fy0,fz1);
    vy0 = LERP(wx, vx0, vx1);
    vx0 = glattice(ix,iy+1,iz+1,fx0,fy1,fz1);
    vx1 = glattice(ix+1,iy+1,iz+1,fx1,fy1,fz1);
    vy1 = LERP(wx, vx0, vx1);
    vz1 = LERP(wy, vy0, vy1);

    return LERP(wz, vz0, vz1);
}