    f                = ff[0];

    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm256_set1_ps(fr->epsfac);
    charge           = mdatoms->chargeA;

    sh_ewald         = _mm256_set1_ps(fr->ic->sh_ewald);
    beta             = _mm256_set1_ps(fr->ic->ewaldcoeff);
    beta2            = _mm256_mul_ps(beta,beta);
    beta3            = _mm256_mul_ps(beta,beta2);

    ewtab            = fr->ic->tabq_coul_FDV0;
    ewtabscale       = _mm256_set1_ps(fr->ic->tabq_scale);
    ewtabhalfspace   = _mm256_set1_ps(0.5/fr->ic->tabq_scale);

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = jnrC = jnrD = jnrE = jnrF = jnrG = jnrH = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;
    j_coord_offsetC = 0;
    j_coord_offsetD = 0;
    j_coord_offsetE = 0;
    j_coord_offsetF = 0;
    j_coord_offsetG = 0;