    int              vdwioffset0;
    __m128d          ix0,iy0,iz0,fix0,fiy0,fiz0,iq0,isai0;
    int              vdwioffset1;
    __m128d          ix1,iy1,iz1,fix1,fiy1,fiz1,iq1,isai1;
    int              vdwioffset2;
    __m128d          ix2,iy2,iz2,fix2,fiy2,fiz2,iq2,isai2;
    int              vdwjidx0A,vdwjidx0B;
    __m128d          jx0,jy0,jz0,fjx0,fjy0,fjz0,jq0,isaj0;
    __m128d          dx00,dy00,dz00,rsq00,rinv00,rinvsq00,r00,qq00,c6_00,c12_00;
    __m128d          dx10,dy10,dz10,rsq10,rinv10,rinvsq10,r10,qq10,c6_10,c12_10;
    __m128d          dx20,dy20,dz20,rsq20,rinv20,rinvsq20,r20,qq20,c6_20,c12_20;
    __m128d          velec,felec,velecsum,facel,crf,krf,krf2;
    real             *charge;
    __m128d          dummy_mask,cutoff_mask;
    __m128d          signbit   = gmx_mm_castsi128_pd( _mm_set_epi32(0x80000000,0x00000000,0x80000000,0x00000000) );
    __m128d          one     = _mm_set1_pd(1.0);
    __m128d          two     = _mm_set1_pd(2.0);
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
    facel            = _mm_set1_pd(fr->epsfac);
    charge           = mdatoms->chargeA;
    krf              = _mm_set1_pd(fr->ic->k_rf);