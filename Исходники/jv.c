double jv(double n, double x)
{
    double k, q, t, y, an;
    int i, sign, nint;

    nint = 0;			/* Flag for integer n */
    sign = 1;			/* Flag for sign inversion */
    an = fabs(n);
    y = floor(an);
    if (y == an) {
        nint = 1;
        i = an - 16384.0 * floor(an / 16384.0);
        if (n < 0.0) {
            if (i & 1)
                sign = -sign;
            n = an;
        }
        if (x < 0.0) {
            if (i & 1)
                sign = -sign;
            x = -x;
        }
        if (n == 0.0)
            return (j0(x));
        if (n == 1.0)
            return (sign * j1(x));
    }

    if ((x < 0.0) && (y != an)) {
        mtherr("Jv", DOMAIN);
        y = NPY_NAN;
        goto done;
    }

    if (x == 0 && n < 0 && !nint) {
        mtherr("Jv", OVERFLOW);
        return NPY_INFINITY / gamma(n + 1);
    }

    y = fabs(x);

    if (y * y < fabs(n + 1) * MACHEP) {
        return pow(0.5 * x, n) / gamma(n + 1);
    }

    k = 3.6 * sqrt(y);
    t = 3.6 * sqrt(an);
    if ((y < t) && (an > 21.0))
        return (sign * jvs(n, x));
    if ((an < k) && (y > 21.0))
        return (sign * hankel(n, x));

    if (an < 500.0) {
        /* Note: if x is too large, the continued fraction will fail; but then the
         * Hankel expansion can be used. */
        if (nint != 0) {
            k = 0.0;
            q = recur(&n, x, &k, 1);
            if (k == 0.0) {
                y = j0(x) / q;
                goto done;
            }
            if (k == 1.0) {
                y = j1(x) / q;
                goto done;
            }
        }

        if (an > 2.0 * y)
            goto rlarger;

        if ((n >= 0.0) && (n < 20.0)
                && (y > 6.0) && (y < 20.0)) {
            /* Recur backwards from a larger value of n */
rlarger:
            k = n;

            y = y + an + 1.0;
            if (y < 30.0)
                y = 30.0;
            y = n + floor(y - n);
            q = recur(&y, x, &k, 0);
            y = jvs(y, x) * q;
            goto done;
        }

        if (k <= 30.0) {
            k = 2.0;
        }
        else if (k < 90.0) {
            k = (3 * k) / 4;
        }
        if (an > (k + 3.0)) {
            if (n < 0.0)
                k = -k;
            q = n - floor(n);
            k = floor(k) + q;
            if (n > 0.0)
                q = recur(&n, x, &k, 1);
            else {
                t = k;
                k = n;
                q = recur(&t, x, &k, 1);
                k = t;
            }
            if (q == 0.0) {
underf:
                y = 0.0;
                goto done;
            }
        }
        else {
            k = n;
            q = 1.0;
        }

        /* boundary between convergence of
         * power series and Hankel expansion
         */
        y = fabs(k);
        if (y < 26.0)
            t = (0.0083 * y + 0.09) * y + 12.9;
        else
            t = 0.9 * y;

        if (x > t)
            y = hankel(k, x);
        else
            y = jvs(k, x);
#if CEPHES_DEBUG
        printf("y = %.16e, recur q = %.16e\n", y, q);
#endif
        if (n > 0.0)
            y /= q;
        else
            y *= q;
    }

    else {
        /* For large n, use the uniform expansion or the transitional expansion.
         * But if x is of the order of n**2, these may blow up, whereas the
         * Hankel expansion will then work.
         */
        if (n < 0.0) {
            mtherr("Jv", TLOSS);
            y = NPY_NAN;
            goto done;
        }
        t = x / n;
        t /= n;
        if (t > 0.3)
            y = hankel(n, x);
        else
            y = jnx(n, x);
    }

done:
    return (sign * y);
}