    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    nvdwtype         = fr->ntype;
    vdwparam         = fr->nbfp;
    vdwtype          = mdatoms->typeA;

    rcutoff_scalar   = fr->rvdw;
    rcutoff          = _mm_set1_ps(rcutoff_scalar);
    rcutoff2         = _mm_mul_ps(rcutoff,rcutoff);

    sh_vdw_invrcut6  = _mm_set1_ps(fr->ic->sh_invrc6);
    rvdw             = _mm_set1_ps(fr->rvdw);

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = jnrC = jnrD = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;
    j_coord_offsetC = 0;
    j_coord_offsetD = 0;

    outeriter        = 0;
    inneriter        = 0;

    for(iidx=0;iidx<4*DIM;iidx++)