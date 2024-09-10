    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;
    shiftidx         = nlist->shift;
    gid              = nlist->gid;
    shiftvec         = fr->shift_vec[0];
    fshift           = fr->fshift[0];
    facel            = _mm_set1_ps(fr->ic->epsfac);
    charge           = mdatoms->chargeA;
    nvdwtype         = fr->ntype;
    vdwparam         = fr->nbfp;
    vdwtype          = mdatoms->typeA;
    vdwgridparam     = fr->ljpme_c6grid;
    sh_lj_ewald	     = _mm_set1_ps(fr->ic->sh_lj_ewald);
    ewclj            = _mm_set1_ps(fr->ic->ewaldcoeff_lj);
    ewclj2	     = _mm_mul_ps(minus_one,_mm_mul_ps(ewclj,ewclj));

    sh_ewald         = _mm_set1_ps(fr->ic->sh_ewald);
    ewtab            = fr->ic->tabq_coul_FDV0;
    ewtabscale       = _mm_set1_ps(fr->ic->tabq_scale);
    ewtabhalfspace   = _mm_set1_ps(0.5/fr->ic->tabq_scale);

    /* When we use explicit cutoffs the value must be identical for elec and VdW, so use elec as an arbitrary choice */
    rcutoff_scalar   = fr->ic->rcoulomb;
    rcutoff          = _mm_set1_ps(rcutoff_scalar);
    rcutoff2         = _mm_mul_ps(rcutoff,rcutoff);

    sh_vdw_invrcut6  = _mm_set1_ps(fr->ic->sh_invrc6);
    rvdw             = _mm_set1_ps(fr->ic->rvdw);

    /* Avoid stupid compiler warnings */