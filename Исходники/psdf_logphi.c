static void
psdflp_do(const PSDFLPArgs *args, GwyDataField *dfield, GwyDataField *lpsdf)
{
    enum { N = 4 };

    GwyDataField *reout, *imout;
    gint pxres, pyres, fxres, fyres;
    gint i, j, fi, pi;
    gdouble *ldata, *redata, *imdata;
    gdouble *cosphi, *sinphi;
    gdouble xreal, yreal, f0, f_max, b, p;

    reout = gwy_data_field_new_alike(dfield, FALSE);
    imout = gwy_data_field_new_alike(dfield, FALSE);
    gwy_data_field_2dfft(dfield, NULL, reout, imout,
                         args->window, GWY_TRANSFORM_DIRECTION_FORWARD,
                         GWY_INTERPOLATION_ROUND, /* Ignored */
                         TRUE, 1);

    pxres = reout->xres;
    pyres = reout->yres;
    redata = gwy_data_field_get_data(reout);
    imdata = gwy_data_field_get_data(imout);
    for (i = 0; i < pxres*pyres; i++)
        redata[i] = redata[i]*redata[i] + imdata[i]*imdata[i];
    gwy_data_field_2dfft_humanize(reout);
    gwy_data_field_filter_gaussian(reout, args->sigma);
    for (i = 0; i < pxres*pyres; i++)
        redata[i] = sqrt(redata[i]);

    fxres = pxres/2;
    fyres = pyres/2;
    gwy_data_field_resample(lpsdf, fxres, fyres, GWY_INTERPOLATION_NONE);
    ldata = gwy_data_field_get_data(lpsdf);

    xreal = dfield->xreal;
    yreal = dfield->yreal;
    f0 = 2.0/MIN(xreal, yreal);
    f_max = 0.5*MIN(pxres/xreal, pyres/yreal);
    if (f_max <= f0) {
        g_warning("Minimum frequency is not smaller than maximum frequency.");
    }
    b = log(f_max/f0)/fyres;

    /* Incorporate some prefactors to sinphi[] and cosphi[], knowing that
     * cosine is only ever used for x and sine for y frequencies. */
    cosphi = g_new(gdouble, (N+1)*fxres);
    sinphi = g_new(gdouble, (N+1)*fxres);
    for (j = 0; j < fxres; j++) {
        gdouble phi_from = 2.0*G_PI*j/fxres;
        gdouble phi_to = 2.0*G_PI*(j + 1.0)/fxres;

        for (pi = 0; pi <= N; pi++) {
            gdouble phi = ((pi + 0.5)*phi_from + (N - 0.5 - pi)*phi_to)/N;
            cosphi[j*(N+1) + pi] = cos(phi)*xreal;
            sinphi[j*(N+1) + pi] = sin(phi)*yreal;
        }
    }

    for (i = 0; i < fyres; i++) {
        gdouble f_from = f0*exp(b*i);
        gdouble f_to = f0*exp(b*(i + 1.0));

        for (j = 0; j < fxres; j++) {
            const gdouble *cosphi_j = cosphi + j*(N+1);
            const gdouble *sinphi_j = sinphi + j*(N+1);
            guint n = 0;
            gdouble s = 0.0;

            for (fi = 0; fi <= N; fi++) {
                gdouble f = ((fi + 0.5)*f_from + (N - 0.5 - fi)*f_to)/N;
                for (pi = 0; pi <= N; pi++) {
                    gdouble x = f*cosphi_j[pi] + pxres/2.0,
                            y = f*sinphi_j[pi] + pyres/2.0;

                    if (G_UNLIKELY(x < 0.5
                                   || y < 0.5
                                   || x > pxres - 1.5
                                   || y > pyres - 1.5))
                        continue;

                    p = gwy_data_field_get_dval(reout, x, y,
                                                GWY_INTERPOLATION_SCHAUM);
                    s += p;
                    n++;
                }
            }

            if (!n)
                n = 1;

            ldata[i*fxres + j] = 2.0*G_PI/fxres * s/n*(f_to - f_from);
        }
    }

    g_object_unref(imout);
    g_object_unref(reout);

    gwy_data_field_set_xreal(lpsdf, 2.0*G_PI);
    gwy_data_field_set_xoffset(lpsdf, 0.0);
    gwy_data_field_set_yreal(lpsdf, log(f_max/f0));
    gwy_data_field_set_yoffset(lpsdf, log(f0));
    gwy_si_unit_set_from_string(gwy_data_field_get_si_unit_xy(lpsdf), "");
    gwy_si_unit_set_from_string(gwy_data_field_get_si_unit_z(lpsdf), "");
    gwy_data_field_normalize(lpsdf);
}