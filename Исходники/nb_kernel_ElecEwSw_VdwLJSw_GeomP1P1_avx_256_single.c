    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm256_set1_ps(fr->epsfac);
    charge           = mdatoms->chargeA;
    nvdwtype         = fr->ntype;
    vdwparam         = fr->nbfp;
    vdwtype          = mdatoms->typeA;

    sh_ewald         = _mm256_set1_ps(fr->ic->sh_ewald);
    beta             = _mm256_set1_ps(fr->ic->ewaldcoeff);
    beta2            = _mm256_mul_ps(beta,beta);
    beta3            = _mm256_mul_ps(beta,beta2);

    ewtab            = fr->ic->tabq_coul_FDV0;
    ewtabscale       = _mm256_set1_ps(fr->ic->tabq_scale);
    ewtabhalfspace   = _mm256_set1_ps(0.5/fr->ic->tabq_scale);

    /* When we use explicit cutoffs the value must be identical for elec and VdW, so use elec as an arbitrary choice */
    rcutoff_scalar   = fr->rcoulomb;
    rcutoff          = _mm256_set1_ps(rcutoff_scalar);
    rcutoff2         = _mm256_mul_ps(rcutoff,rcutoff);

    rswitch_scalar   = fr->rcoulomb_switch;
    rswitch          = _mm256_set1_ps(rswitch_scalar);
    /* Setup switch parameters */
    d_scalar         = rcutoff_scalar-rswitch_scalar;