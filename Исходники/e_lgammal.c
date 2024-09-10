long double
lgammal(long double x)
{
    long double p, q, w, z, nx;
    int i, nn;

    signgam = 1;

    if (! finite (x))
        return x * x;

    if (x == 0.0L)
    {
        if (signbit (x))
            signgam = -1;
        return one / fabsl (x);
    }

    if (x < 0.0L)
    {
        q = -x;
        p = floorl (q);
        if (p == q)
            return (one / (p - p));
        i = p;
        if ((i & 1) == 0)
            signgam = -1;
        else
            signgam = 1;
        z = q - p;
        if (z > 0.5L)
        {
            p += 1.0L;
            z = p - q;
        }
        z = q * sinl (PIL * z);
        if (z == 0.0L)
            return (signgam * huge * huge);
        w = lgammal (q);
        z = logl (PIL / z) - w;
        return (z);
    }

    if (x < 13.5L)
    {
        p = 0.0L;
        nx = floorl (x + 0.5L);
        nn = nx;
        switch (nn)
        {
        case 0:
            /* log gamma (x + 1) = log(x) + log gamma(x) */
            if (x <= 0.125)
            {
                p = x * neval (x, RN1, NRN1) / deval (x, RD1, NRD1);
            }
            else if (x <= 0.375)
            {
                z = x - 0.25L;
                p = z * neval (z, RN1r25, NRN1r25) / deval (z, RD1r25, NRD1r25);
                p += lgam1r25b;
                p += lgam1r25a;
            }
            else if (x <= 0.625)
            {
                z = x + (1.0L - x0a);
                z = z - x0b;
                p = neval (z, RN1r5, NRN1r5) / deval (z, RD1r5, NRD1r5);
                p = p * z * z;
                p = p + y0b;
                p = p + y0a;
            }
            else if (x <= 0.875)
            {
                z = x - 0.75L;
                p = z * neval (z, RN1r75, NRN1r75) / deval (z, RD1r75, NRD1r75);
                p += lgam1r75b;
                p += lgam1r75a;
            }
            else
            {
                z = x - 1.0L;
                p = z * neval (z, RN2, NRN2) / deval (z, RD2, NRD2);
            }
            p = p - logl (x);
            break;

        case 1:
            if (x < 0.875L)
            {
                if (x <= 0.625)
                {
                    z = x + (1.0L - x0a);
                    z = z - x0b;
                    p = neval (z, RN1r5, NRN1r5) / deval (z, RD1r5, NRD1r5);
                    p = p * z * z;
                    p = p + y0b;
                    p = p + y0a;
                }
                else if (x <= 0.875)
                {
                    z = x - 0.75L;
                    p = z * neval (z, RN1r75, NRN1r75)
                        / deval (z, RD1r75, NRD1r75);
                    p += lgam1r75b;
                    p += lgam1r75a;
                }
                else
                {
                    z = x - 1.0L;
                    p = z * neval (z, RN2, NRN2) / deval (z, RD2, NRD2);
                }
                p = p - logl (x);
            }
            else if (x < 1.0L)
            {
                z = x - 1.0L;
                p = z * neval (z, RNr9, NRNr9) / deval (z, RDr9, NRDr9);
            }
            else if (x == 1.0L)
                p = 0.0L;
            else if (x <= 1.125L)
            {
                z = x - 1.0L;
                p = z * neval (z, RN1, NRN1) / deval (z, RD1, NRD1);
            }
            else if (x <= 1.375)
            {
                z = x - 1.25L;
                p = z * neval (z, RN1r25, NRN1r25) / deval (z, RD1r25, NRD1r25);
                p += lgam1r25b;
                p += lgam1r25a;
            }
            else
            {
                /* 1.375 <= x+x0 <= 1.625 */
                z = x - x0a;
                z = z - x0b;
                p = neval (z, RN1r5, NRN1r5) / deval (z, RD1r5, NRD1r5);
                p = p * z * z;
                p = p + y0b;
                p = p + y0a;
            }
            break;

        case 2:
            if (x < 1.625L)
            {
                z = x - x0a;
                z = z - x0b;
                p = neval (z, RN1r5, NRN1r5) / deval (z, RD1r5, NRD1r5);
                p = p * z * z;
                p = p + y0b;
                p = p + y0a;
            }
            else if (x < 1.875L)
            {
                z = x - 1.75L;
                p = z * neval (z, RN1r75, NRN1r75) / deval (z, RD1r75, NRD1r75);
                p += lgam1r75b;
                p += lgam1r75a;
            }
            else if (x == 2.0L)
                p = 0.0L;
            else if (x < 2.375L)
            {
                z = x - 2.0L;
                p = z * neval (z, RN2, NRN2) / deval (z, RD2, NRD2);
            }
            else
            {
                z = x - 2.5L;
                p = z * neval (z, RN2r5, NRN2r5) / deval (z, RD2r5, NRD2r5);
                p += lgam2r5b;
                p += lgam2r5a;
            }
            break;

        case 3:
            if (x < 2.75)
            {
                z = x - 2.5L;
                p = z * neval (z, RN2r5, NRN2r5) / deval (z, RD2r5, NRD2r5);
                p += lgam2r5b;
                p += lgam2r5a;
            }
            else
            {
                z = x - 3.0L;
                p = z * neval (z, RN3, NRN3) / deval (z, RD3, NRD3);
                p += lgam3b;
                p += lgam3a;
            }
            break;

        case 4:
            z = x - 4.0L;
            p = z * neval (z, RN4, NRN4) / deval (z, RD4, NRD4);
            p += lgam4b;
            p += lgam4a;
            break;

        case 5:
            z = x - 5.0L;
            p = z * neval (z, RN5, NRN5) / deval (z, RD5, NRD5);
            p += lgam5b;
            p += lgam5a;
            break;

        case 6:
            z = x - 6.0L;
            p = z * neval (z, RN6, NRN6) / deval (z, RD6, NRD6);
            p += lgam6b;
            p += lgam6a;
            break;

        case 7:
            z = x - 7.0L;
            p = z * neval (z, RN7, NRN7) / deval (z, RD7, NRD7);
            p += lgam7b;
            p += lgam7a;
            break;

        case 8:
            z = x - 8.0L;
            p = z * neval (z, RN8, NRN8) / deval (z, RD8, NRD8);
            p += lgam8b;
            p += lgam8a;
            break;

        case 9:
            z = x - 9.0L;
            p = z * neval (z, RN9, NRN9) / deval (z, RD9, NRD9);
            p += lgam9b;
            p += lgam9a;
            break;

        case 10:
            z = x - 10.0L;
            p = z * neval (z, RN10, NRN10) / deval (z, RD10, NRD10);
            p += lgam10b;
            p += lgam10a;
            break;

        case 11:
            z = x - 11.0L;
            p = z * neval (z, RN11, NRN11) / deval (z, RD11, NRD11);
            p += lgam11b;
            p += lgam11a;
            break;

        case 12:
            z = x - 12.0L;
            p = z * neval (z, RN12, NRN12) / deval (z, RD12, NRD12);
            p += lgam12b;
            p += lgam12a;
            break;

        case 13:
            z = x - 13.0L;
            p = z * neval (z, RN13, NRN13) / deval (z, RD13, NRD13);
            p += lgam13b;
            p += lgam13a;
            break;
        }
        return p;
    }

    if (x > MAXLGM)
        return (signgam * huge * huge);

    q = ls2pi - x;
    q = (x - 0.5L) * logl (x) + q;
    if (x > 1.0e18L)
        return (q);

    p = 1.0L / (x * x);
    q += neval (p, RASY, NRASY) / x;
    return (q);
}