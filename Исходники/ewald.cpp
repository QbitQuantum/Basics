real do_ewald(t_inputrec *ir,
              rvec x[],        rvec f[],
              real chargeA[],  real chargeB[],
              rvec box,
              t_commrec *cr,   int natoms,
              matrix lrvir,    real ewaldcoeff,
              real lambda,     real *dvdlambda,
              struct gmx_ewald_tab_t *et)
{
    real     factor     = -1.0/(4*ewaldcoeff*ewaldcoeff);
    real     scaleRecip = 4.0*M_PI/(box[XX]*box[YY]*box[ZZ])*ONE_4PI_EPS0/ir->epsilon_r; /* 1/(Vol*e0) */
    real    *charge, energy_AB[2], energy;
    rvec     lll;
    int      lowiy, lowiz, ix, iy, iz, n, q;
    real     tmp, cs, ss, ak, akv, mx, my, mz, m2, scale;
    gmx_bool bFreeEnergy;

    if (cr != NULL)
    {
        if (PAR(cr))
        {
            gmx_fatal(FARGS, "No parallel Ewald. Use PME instead.\n");
        }
    }


    if (!et->eir) /* allocate if we need to */
    {
        snew(et->eir, et->kmax);
        for (n = 0; n < et->kmax; n++)
        {
            snew(et->eir[n], natoms);
        }
        snew(et->tab_xy, natoms);
        snew(et->tab_qxyz, natoms);
    }

    bFreeEnergy = (ir->efep != efepNO);

    clear_mat(lrvir);

    calc_lll(box, lll);
    tabulateStructureFactors(natoms, x, et->kmax, et->eir, lll);

    for (q = 0; q < (bFreeEnergy ? 2 : 1); q++)
    {
        if (!bFreeEnergy)
        {
            charge = chargeA;
            scale  = 1.0;
        }
        else if (q == 0)
        {
            charge = chargeA;
            scale  = 1.0 - lambda;
        }
        else
        {
            charge = chargeB;
            scale  = lambda;
        }
        lowiy        = 0;
        lowiz        = 1;
        energy_AB[q] = 0;
        for (ix = 0; ix < et->nx; ix++)
        {
            mx = ix*lll[XX];
            for (iy = lowiy; iy < et->ny; iy++)
            {
                my = iy*lll[YY];
                if (iy >= 0)
                {
                    for (n = 0; n < natoms; n++)
                    {
                        et->tab_xy[n] = cmul(et->eir[ix][n][XX], et->eir[iy][n][YY]);
                    }
                }
                else
                {
                    for (n = 0; n < natoms; n++)
                    {
                        et->tab_xy[n] = cmul(et->eir[ix][n][XX], conjugate(et->eir[-iy][n][YY]));
                    }
                }
                for (iz = lowiz; iz < et->nz; iz++)
                {
                    mz  = iz*lll[ZZ];
                    m2  = mx*mx+my*my+mz*mz;
                    ak  = exp(m2*factor)/m2;
                    akv = 2.0*ak*(1.0/m2-factor);
                    if (iz >= 0)
                    {
                        for (n = 0; n < natoms; n++)
                        {
                            et->tab_qxyz[n] = rcmul(charge[n], cmul(et->tab_xy[n],
                                                                    et->eir[iz][n][ZZ]));
                        }
                    }
                    else
                    {
                        for (n = 0; n < natoms; n++)
                        {
                            et->tab_qxyz[n] = rcmul(charge[n], cmul(et->tab_xy[n],
                                                                    conjugate(et->eir[-iz][n][ZZ])));
                        }
                    }

                    cs = ss = 0;
                    for (n = 0; n < natoms; n++)
                    {
                        cs += et->tab_qxyz[n].re;
                        ss += et->tab_qxyz[n].im;
                    }
                    energy_AB[q]  += ak*(cs*cs+ss*ss);
                    tmp            = scale*akv*(cs*cs+ss*ss);
                    lrvir[XX][XX] -= tmp*mx*mx;
                    lrvir[XX][YY] -= tmp*mx*my;
                    lrvir[XX][ZZ] -= tmp*mx*mz;
                    lrvir[YY][YY] -= tmp*my*my;
                    lrvir[YY][ZZ] -= tmp*my*mz;
                    lrvir[ZZ][ZZ] -= tmp*mz*mz;
                    for (n = 0; n < natoms; n++)
                    {
                        /*tmp=scale*ak*(cs*tab_qxyz[n].im-ss*tab_qxyz[n].re);*/
                        tmp       = scale*ak*(cs*et->tab_qxyz[n].im-ss*et->tab_qxyz[n].re);
                        f[n][XX] += tmp*mx*2*scaleRecip;
                        f[n][YY] += tmp*my*2*scaleRecip;
                        f[n][ZZ] += tmp*mz*2*scaleRecip;
#if 0
                        f[n][XX] += tmp*mx;
                        f[n][YY] += tmp*my;
                        f[n][ZZ] += tmp*mz;
#endif
                    }
                    lowiz = 1-et->nz;
                }
                lowiy = 1-et->ny;
            }
        }
    }

    if (!bFreeEnergy)
    {
        energy = energy_AB[0];
    }
    else
    {
        energy      = (1.0 - lambda)*energy_AB[0] + lambda*energy_AB[1];
        *dvdlambda += scaleRecip*(energy_AB[1] - energy_AB[0]);
    }

    lrvir[XX][XX] = -0.5*scaleRecip*(lrvir[XX][XX]+energy);
    lrvir[XX][YY] = -0.5*scaleRecip*(lrvir[XX][YY]);
    lrvir[XX][ZZ] = -0.5*scaleRecip*(lrvir[XX][ZZ]);
    lrvir[YY][YY] = -0.5*scaleRecip*(lrvir[YY][YY]+energy);
    lrvir[YY][ZZ] = -0.5*scaleRecip*(lrvir[YY][ZZ]);
    lrvir[ZZ][ZZ] = -0.5*scaleRecip*(lrvir[ZZ][ZZ]+energy);

    lrvir[YY][XX] = lrvir[XX][YY];
    lrvir[ZZ][XX] = lrvir[XX][ZZ];
    lrvir[ZZ][YY] = lrvir[YY][ZZ];

    energy *= scaleRecip;

    return energy;
}