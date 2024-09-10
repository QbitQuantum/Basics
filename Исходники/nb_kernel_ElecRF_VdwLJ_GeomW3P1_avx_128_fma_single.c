    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm_set1_ps(fr->epsfac);
    charge           = mdatoms->chargeA;
    krf              = _mm_set1_ps(fr->ic->k_rf);
    krf2             = _mm_set1_ps(fr->ic->k_rf*2.0);
    crf              = _mm_set1_ps(fr->ic->c_rf);
    nvdwtype         = fr->ntype;
    vdwparam         = fr->nbfp;
    vdwtype          = mdatoms->typeA;

    /* Setup water-specific parameters */
    inr              = nlist->iinr[0];
    iq0              = _mm_mul_ps(facel,_mm_set1_ps(charge[inr+0]));
    iq1              = _mm_mul_ps(facel,_mm_set1_ps(charge[inr+1]));
    iq2              = _mm_mul_ps(facel,_mm_set1_ps(charge[inr+2]));
    vdwioffset0      = 2*nvdwtype*vdwtype[inr+0];

    /* Avoid stupid compiler warnings */
    jnrA = jnrB = jnrC = jnrD = 0;
    j_coord_offsetA = 0;
    j_coord_offsetB = 0;
    j_coord_offsetC = 0;
    j_coord_offsetD = 0;

    outeriter        = 0;
    inneriter        = 0;

    for(iidx=0;iidx<4*DIM;iidx++)