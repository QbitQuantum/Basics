void
Cheby2D_Test(Cheby2D *cheby, int nx_test, int ny_test,
        void
        (*func)(long double *x, long double *y, 
            int nx, int ny, long double *z, void *info),
        void *info,
        long double *residualRMS, long double *residualMAV)
{
    int ix_test, iy_test;
    long double  fprime;
    long double sdiff, ssdiff, maxdiff, diff;
    long double *f = (long double*)malloc(nx_test*ny_test*sizeof(long double));
    long double *x = (long double *)malloc(nx_test*sizeof(long double));
    long double *y = (long double *)malloc(ny_test*sizeof(long double));

    sdiff=ssdiff=maxdiff=0.0L;

    // call func to get actual values on grid
    for (iy_test=0; iy_test<ny_test; iy_test++)
        y[iy_test] = -1.0L + 2.0L*(iy_test+0.5L)/ny_test; 
    for (ix_test=0; ix_test<nx_test; ix_test++)
        x[ix_test] = -1.0L + 2.0L*(ix_test+0.5L)/nx_test; 
    func(x, y, nx_test, ny_test, f, info);

    // compare
    for (iy_test=0; iy_test<ny_test; iy_test++)
    {
        for (ix_test=0; ix_test<nx_test; ix_test++)
        {
            fprime = Cheby2D_Evaluate(cheby, x[ix_test], y[iy_test]);
            diff = f[iy_test*nx_test+ix_test]-fprime;

#if 0
            {
                // redwards hack to simulate 1-D polyco.. first get prediction from
                // centre freq
                long double phase1d = Cheby2D_Evaluate(cheby, x[ix_test], 0.0);
                // second, get instantaneous freq at band center
                long double dx = 1.0e-5L;
                long double freq1 = 
                    (Cheby2D_Evaluate(cheby, x[ix_test]+dx*0.5L, y[iy_test])-
                     Cheby2D_Evaluate(cheby, x[ix_test]-dx*0.5L, y[iy_test])) / dx;
                long double freq=
                    (Cheby2D_Evaluate(cheby, x[ix_test]+dx*0.5L, 0.0L)-
                     Cheby2D_Evaluate(cheby, x[ix_test]-dx*0.5L, 0.0L)) / dx;
                long double skyfreq = 653.0L+y[iy_test]*32.0L; // MHzx
                long double dmdelay = 1.0L/2.41e-4L *(1.0L/ (skyfreq*skyfreq) -1.0L/(653.0L*653.0L))
                    *48.901787L; // s
                long double dphase = -freq*dmdelay;
                long double diff1d = f[iy_test*nx_test+ix_test]-(phase1d+dphase);

                freq *= 2.0L/0.03L / 86400.0L; // normalized->day^-1->Hz
                freq1 *= 2.0L/0.03L / 86400.0L;

                //             printf("YYY %Lf %Lf %Lf\n", freq, dmdelay, dphase);
                //       printf("%Lf %Lf %Lg %Lg %Lg %Lg %Lg XXX\n", x[ix_test], y[iy_test], 
                //   	     f[iy_test*nx_test+ix_test], fprime, diff, diff1d, 
                // 	     (freq1-freq)/freq);
            }
#endif
            if (fabs(diff) > maxdiff)
                maxdiff = fabs(diff);
            sdiff += diff;
            ssdiff += diff*diff;
        }
        //      printf("\n");
    }
    sdiff /=nx_test*ny_test;
    *residualRMS = sqrtl(ssdiff/(nx_test*ny_test));
    *residualMAV = maxdiff;

    free(f);
    free(x);
    free(y);
}