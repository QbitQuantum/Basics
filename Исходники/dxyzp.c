double xyzp(double a, double b, double c, double *x, double *y, double *z,
            int n, int r_max)
{
    __builtin_assume_aligned(x, BYTEALIGN);
    __builtin_assume_aligned(y, BYTEALIGN);
    __builtin_assume_aligned(z, BYTEALIGN);

    int i, r;
    struct timespec ts_start, ts_end;
    double runtime;

    int midpt = n / 2;
    double sum;

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts_start);
    for (r = 0; r < r_max; r++) {
        //#pragma unroll(8)
        for (i = 0; i < n; i++)
            //z[i] = x[i] + y[i] + z[i];
            //z[i] = x[i] * y[i] + z[i];
            //z[i] = a * x[i] + y[i] + z[i];
            //z[i] = a * x[i] + b * y[i] + z[i];
            //z[i] = a * x[i] + b * y[i] + c * z[i];
            //z[i] = a * x[i] + b * y[i] + c;
            z[i] = 0.25 * x[i] * y[i];
            //z[i] = 0.25 + x[i] + y[i];
            //z[i] = a * x[i] * y[i];
            //z[i] = a + x[i] + y[i];
        // To prevent outer loop removal during optimisation
        if (y[midpt] < 0.) dummy(a, x, y, z);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts_end);

    runtime = (double) (ts_end.tv_sec - ts_start.tv_sec)
        + (double) (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9;

    return runtime;
}