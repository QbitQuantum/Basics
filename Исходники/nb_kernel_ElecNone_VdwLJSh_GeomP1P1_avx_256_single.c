    real             *fjptrA,*fjptrB,*fjptrC,*fjptrD,*fjptrE,*fjptrF,*fjptrG,*fjptrH;
    real             scratch[4*DIM];
    __m256           tx,ty,tz,fscal,rcutoff,rcutoff2,jidxall;
    real *           vdwioffsetptr0;
    __m256           ix0,iy0,iz0,fix0,fiy0,fiz0,iq0,isai0;
    int              vdwjidx0A,vdwjidx0B,vdwjidx0C,vdwjidx0D,vdwjidx0E,vdwjidx0F,vdwjidx0G,vdwjidx0H;
    __m256           jx0,jy0,jz0,fjx0,fjy0,fjz0,jq0,isaj0;
    __m256           dx00,dy00,dz00,rsq00,rinv00,rinvsq00,r00,qq00,c6_00,c12_00;
    int              nvdwtype;
    __m256           rinvsix,rvdw,vvdw,vvdw6,vvdw12,fvdw,fvdw6,fvdw12,vvdwsum,sh_vdw_invrcut6;
    int              *vdwtype;
    real             *vdwparam;
    __m256           one_sixth   = _mm256_set1_ps(1.0/6.0);
    __m256           one_twelfth = _mm256_set1_ps(1.0/12.0);
    __m256           dummy_mask,cutoff_mask;
    __m256           signbit = _mm256_castsi256_ps( _mm256_set1_epi32(0x80000000) );
    __m256           one     = _mm256_set1_ps(1.0);
    __m256           two     = _mm256_set1_ps(2.0);
    x                = xx[0];
    f                = ff[0];

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