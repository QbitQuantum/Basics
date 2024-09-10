    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm256_set1_ps(fr->epsfac);
    charge           = mdatoms->chargeA;
    krf              = _mm256_set1_ps(fr->ic->k_rf);
    krf2             = _mm256_set1_ps(fr->ic->k_rf*2.0);
    crf              = _mm256_set1_ps(fr->ic->c_rf);

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq0              = _mm256_mul_ps(facel,_mm256_set1_ps(charge[inr+0]));
    iq1              = _mm256_mul_ps(facel,_mm256_set1_ps(charge[inr+1]));
    iq2              = _mm256_mul_ps(facel,_mm256_set1_ps(charge[inr+2]));

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = jnrC = jnrD = jnrE = jnrF = jnrG = jnrH = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;
    j_coord_offsetC = 0;
    j_coord_offsetD = 0;
    j_coord_offsetE = 0;
    j_coord_offsetF = 0;
    j_coord_offsetG = 0;
    j_coord_offsetH = 0;

    outeriter        = 0;