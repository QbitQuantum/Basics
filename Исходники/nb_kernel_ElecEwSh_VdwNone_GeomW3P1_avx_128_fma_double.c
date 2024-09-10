    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm_set1_pd(fr->epsfac);
    charge           = mdatoms->chargeA;

    sh_ewald         = _mm_set1_pd(fr->ic->sh_ewald);
    ewtab            = fr->ic->tabq_coul_FDV0;
    ewtabscale       = _mm_set1_pd(fr->ic->tabq_scale);
    ewtabhalfspace   = _mm_set1_pd(0.5/fr->ic->tabq_scale);

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq0              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+0]));
    iq1              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+1]));
    iq2              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+2]));

    /* When we use explicit cutoffs the value must be identical for elec and VdW, so use elec as an arbitrary choice */
    rcutoff_scalar   = fr->rcoulomb;
    rcutoff          = _mm_set1_pd(rcutoff_scalar);
    rcutoff2         = _mm_mul_pd(rcutoff,rcutoff);

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;

    outeriter        = 0;
    inneriter        = 0;