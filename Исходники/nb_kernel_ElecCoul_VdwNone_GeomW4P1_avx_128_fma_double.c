    f                = ff[0];

    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm_set1_pd(fr->epsfac);
    charge           = mdatoms->chargeA;

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq1              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+1]));
    iq2              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+2]));
    iq3              = _mm_mul_pd(facel,_mm_set1_pd(charge[inr+3]));

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;

    outeriter        = 0;
    inneriter        = 0;

    /* Start outer loop over neighborlists */
    for(iidx=0; iidx<nri; iidx++)
    {
        /* Load shift vector for this list */