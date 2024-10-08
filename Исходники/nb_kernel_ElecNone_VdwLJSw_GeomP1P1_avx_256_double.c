    int              *iinr,*jindex,*jjnr,*shiftidx,*gid;
    real             rcutoff_scalar;
    real             *shiftvec,*fshift,*x,*f;
    real             *fjptrA,*fjptrB,*fjptrC,*fjptrD;
    real             scratch[4*DIM];
    __m256d          tx,ty,tz,fscal,rcutoff,rcutoff2,jidxall;
    real *           vdwioffsetptr0;
    __m256d          ix0,iy0,iz0,fix0,fiy0,fiz0,iq0,isai0;
    int              vdwjidx0A,vdwjidx0B,vdwjidx0C,vdwjidx0D;
    __m256d          jx0,jy0,jz0,fjx0,fjy0,fjz0,jq0,isaj0;
    __m256d          dx00,dy00,dz00,rsq00,rinv00,rinvsq00,r00,qq00,c6_00,c12_00;
    int              nvdwtype;
    __m256d          rinvsix,rvdw,vvdw,vvdw6,vvdw12,fvdw,fvdw6,fvdw12,vvdwsum,sh_vdw_invrcut6;
    int              *vdwtype;
    real             *vdwparam;
    __m256d          one_sixth   = _mm256_set1_pd(1.0/6.0);
    __m256d          one_twelfth = _mm256_set1_pd(1.0/12.0);
    __m256d          rswitch,swV3,swV4,swV5,swF2,swF3,swF4,d,d2,sw,dsw;
    real             rswitch_scalar,d_scalar;
    __m256d          dummy_mask,cutoff_mask;
    __m128           tmpmask0,tmpmask1;
    __m256d          signbit = _mm256_castsi256_pd( _mm256_set1_epi32(0x80000000) );
    __m256d          one     = _mm256_set1_pd(1.0);
    __m256d          two     = _mm256_set1_pd(2.0);
    x                = xx[0];
    f                = ff[0];

    nri              = nlist->nri;
    iinr             = nlist->iinr;
    jindex           = nlist->jindex;
    jjnr             = nlist->jjnr;