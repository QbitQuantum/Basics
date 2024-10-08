    __m256           tx,ty,tz,fscal,rcutoff,rcutoff2,jidxall;
    real *           vdwioffsetptr0;
    __m256           ix0,iy0,iz0,fix0,fiy0,fiz0,iq0,isai0;
    int              vdwjidx0A,vdwjidx0B,vdwjidx0C,vdwjidx0D,vdwjidx0E,vdwjidx0F,vdwjidx0G,vdwjidx0H;
    __m256           jx0,jy0,jz0,fjx0,fjy0,fjz0,jq0,isaj0;
    __m256           dx00,dy00,dz00,rsq00,rinv00,rinvsq00,r00,qq00,c6_00,c12_00;
    __m256           velec,felec,velecsum,facel,crf,krf,krf2;
    real             *charge;
    __m256i          vfitab;
    __m128i          vfitab_lo,vfitab_hi;
    __m128i          ifour       = _mm_set1_epi32(4);
    __m256           rt,vfeps,vftabscale,Y,F,G,H,Heps,Fp,VV,FF;
    real             *vftab;
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
    facel            = _mm256_set1_ps(fr->epsfac);
    charge           = mdatoms->chargeA;
