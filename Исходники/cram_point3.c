/* Compute scattering angle, scattering angle azimuth, dip angle, dip angle azimuth
   from source and receiver elevation/azimuth angles */
static void sf_cram_point3_angles (float sb, float sa, float hb, float ha,
                                   float *oa, float *oz, float *da, float *dz) {
    float sv[3], hv[3], ov[3], dv[3], pv[3], nv[3], mv[3];
    float a, l, dl, dll;

    /* Create shot and receiver vectors */
    sv[0] = cosf (sb);          /* z */
    sv[1] = sinf (sb)*cosf (sa); /* x */
    sv[2] = sinf (sb)*sinf (sa); /* y */
    hv[0] = cosf (hb);          /* z */
    hv[1] = sinf (hb)*cosf (ha); /* x */
    hv[2] = sinf (hb)*sinf (ha); /* y */

    /* Scattering angle vector */
    ov[0] = -sv[0] + hv[0];
    ov[1] = -sv[1] + hv[1];
    ov[2] = -sv[2] + hv[2];
    /* Dip vector */
    dv[0] = sv[0] + hv[0];
    dv[1] = sv[1] + hv[1];
    dv[2] = sv[2] + hv[2];
    dl = sqrtf (dv[0]*dv[0] + dv[1]*dv[1] + dv[2]*dv[2]);

    if (fabsf (sb - hb) > 1e-4 ||
        fabsf (sa - ha) > 1e-4) {
        /* Scattering angle - dot product between vectors */
        a = sv[0]*hv[0] + sv[1]*hv[1] + sv[2]*hv[2];
        if (a > 1.0)
            a = 1.0;
        if (a < -1.0)
            a = -1.0;
        *oa = acosf (a);
        /* Cross-product between the two vectors - contained in the reflection plane */
        pv[0] = ov[1]*dv[2] - ov[2]*dv[1];
        pv[1] = ov[2]*dv[0] - ov[0]*dv[2];
        pv[2] = ov[0]*dv[1] - ov[1]*dv[0];
        /* Cross-product between the x direction (reference vector) and the dip -
           contained in the reflection plane */
        nv[0] = dv[2];  /* 1.0*dv[2] - 0.0*dv[1] */
        nv[1] = 0.0;    /* 0.0*dv[0] - 0.0*dv[2] */
        nv[2] = -dv[0]; /* 0.0*dv[1] - 1.0*dv[0] */
        /* Scattering angle azimuth - angle between the above two vectors in the
           reflection plane - see Fomel and Sava (2005) */
        dll = sqrtf (pv[0]*pv[0] + pv[1]*pv[1] + pv[2]*pv[2])*
              sqrtf (nv[0]*nv[0] + nv[1]*nv[1] + nv[2]*nv[2]);
        a = (pv[0]*nv[0] + pv[1]*nv[1] + pv[2]*nv[2])/dll;
        if (a > 1.0)
            a = 1.0;
        if (a < -1.0)
            a = -1.0;
        *oz = acosf (a);
        /* Cross product between the above two vectors - should be parallel
           to the dip */
        mv[0] = nv[1]*pv[2] - nv[2]*pv[1];
        mv[1] = nv[2]*pv[0] - nv[0]*pv[2];
        mv[2] = nv[0]*pv[1] - nv[1]*pv[0];
        dll = dl*sqrtf (mv[0]*mv[0] + mv[1]*mv[1] + mv[2]*mv[2]);
        /* Check if it has the same direction with the dip */
        a = (dv[0]*mv[0] + dv[1]*mv[1] + dv[2]*mv[2])/dll;
        if (a < 0.0) /* Otherwise, flip the scattering azimuth */
            *oz = SF_PI - *oz;
        else
            *oa *= -1.0;
    } else {
        /* Scattering angle */
        *oa = 0.0;
        /* Scattering angle azimuth */
        *oz = 0.0;
    }

    /* Dip angle - angle between z axis and dv */
    a = dv[0]/dl;
    *da = acosf (a);
    /* Dip angle azimuth - angle between projection
       of dv onto x-y plane and x component of dv */
    l = hypotf (dv[1], dv[2]);
    if (l != 0.0) {
        a = dv[1]/l;
        if (a > 1.0)
            a = 1.0;
        if (a < -1.0)
            a = -1.0;
        *dz = acosf (a);
        if (dv[2] < 0.0)
            *dz = SF_PI - *dz;
        else
            *da *= -1.0;
    } else {
        *dz = 0.0;
    }
}