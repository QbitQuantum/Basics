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
    vdwgridparam     = fr->ljpme_c6grid;
    sh_lj_ewald	     = _mm256_set1_ps(fr->ic->sh_lj_ewald);
    ewclj            = _mm256_set1_ps(fr->ewaldcoeff_lj);
    ewclj2           = _mm256_mul_ps(minus_one,_mm256_mul_ps(ewclj,ewclj));

    sh_ewald         = _mm256_set1_ps(fr->ic->sh_ewald);
    beta             = _mm256_set1_ps(fr->ic->ewaldcoeff_q);
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