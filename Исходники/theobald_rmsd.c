real ls_rmsd2_aligned_T_g(const int nrealatoms, const int npaddedatoms, const int rowstride,
                          const float* aT, const float* bT, const real G_a, const real G_b)
{
    /* Structure setup for this function:
     *
     *   structures are stored axis major, possibly with extra padding to ensure you
     *   meet two constraints:
     *       - the number of elements in a row must be a multiple of 4
     *       - the first element in each row must be aligned to a 16 byte boundary
     *
     *   note that if you meet the second condition for the first row, and meet the
     *   first condition, the alignment will automatically be satisfied for every row.
     *
     *   the layout in memory for a structure of 7 atoms would look like this:
     *
     *       x0 x1 x2 x3 x4 x5 x6 0
     *       y0 y1 y2 y3 y4 y5 y6 0
     *       z0 z1 z2 z3 z4 z5 z6 0
     *
     *   if your structure has a number of atoms that is not a multiple of 4, you must
     *   pad it out to a multiple of 4 using zeros (using anything other than zero will
     *   make the calculation go wrong).
     *
     *   arguments:
     *       nrealatoms:   the *actual* number of atoms in the structure
     *
     *       npaddedatoms: the number of atoms in the structure including padding atoms;
     *                     should equal nrealatoms rounded up to the next multiple of 4
     *
     *       rowstride:    the offset in elements between rows in the arrays. will prob
     *                     be equal to npaddedatoms, but you might use something else if
     *                     (for example) you were subsetting the structure
     *
     *       aT:           pointer to start of first structure (A). should be aligned to
     *                     a 16-byte boundary
     *
     *       bT:           pointer to start of second structure (B). should be aligned to
     *                     a 16-byte boundary
     *
     *       G_a:          trace of A'A
     *
     *       G_b:          trace of B'B
     */

  /* printf ("# theo rmsd: nreal = %d npadded = %d rowstride = %d Ga = %f Gb = %f\n", */
  /* 	  nrealatoms, npaddedatoms, rowstride, G_a, G_b); */
            
	int nIndex;
    // Will have 3 garbage elements at the end
    float M[12] __attribute__ ((aligned (16)));

    const float* aTx = aT;
    const float* aTy = aT+rowstride;
    const float* aTz = aT+2*rowstride;
    const float* bTx = bT;
    const float* bTy = bT+rowstride;
    const float* bTz = bT+2*rowstride;


    // npaddedatoms must be a multiple of 4
    int niters = npaddedatoms >> 2;
    __m128 xx,xy,xz,yx,yy,yz,zx,zy,zz;
    __m128 ax,ay,az,b;
    __m128 t0,t1,t2;
    // Prologue
    xx = _mm_xor_ps(xx,xx);
    xy = _mm_xor_ps(xy,xy);
    xz = _mm_xor_ps(xz,xz);
    yx = _mm_xor_ps(yx,yx);
    yy = _mm_xor_ps(yy,yy);
    yz = _mm_xor_ps(yz,yz);
    zx = _mm_xor_ps(zx,zx);
    zy = _mm_xor_ps(zy,zy);
    zz = _mm_xor_ps(zz,zz);
    for (int k = 0; k < niters; k++) {
        ax = _mm_load_ps(aTx);
        ay = _mm_load_ps(aTy);
        az = _mm_load_ps(aTz);

        b = _mm_load_ps(bTx);
        t0 = ax;
        t1 = ay;
        t2 = az;

        t0 = _mm_mul_ps(t0,b);
        t1 = _mm_mul_ps(t1,b);
        t2 = _mm_mul_ps(t2,b);

        xx = _mm_add_ps(xx,t0);
        yx = _mm_add_ps(yx,t1);
        zx = _mm_add_ps(zx,t2);

        b = _mm_load_ps(bTy);
        t0 = ax;
        t1 = ay;
        t2 = az;

        t0 = _mm_mul_ps(t0,b);
        t1 = _mm_mul_ps(t1,b);
        t2 = _mm_mul_ps(t2,b);

        xy = _mm_add_ps(xy,t0);
        yy = _mm_add_ps(yy,t1);
        zy = _mm_add_ps(zy,t2);

        b = _mm_load_ps(bTz);

        ax = _mm_mul_ps(ax,b);
        ay = _mm_mul_ps(ay,b);
        az = _mm_mul_ps(az,b);

        xz = _mm_add_ps(xz,ax);
        yz = _mm_add_ps(yz,ay);
        zz = _mm_add_ps(zz,az);

        aTx += 4;
        aTy += 4;
        aTz += 4;
        bTx += 4;
        bTy += 4;
        bTz += 4;
    }
    // Epilogue - reduce 4 wide vectors to one wide
   /*xmm07 = xx0 xx1 xx2 xx3
     xmm08 = xy0 xy1 xy2 xy3
     xmm09 = xz0 xz1 xz2 xz3
     xmm10 = yx0 yx1 yx2 yx3
     xmm11 = yy0 yy1 yy2 yy3
     xmm12 = yz0 yz1 yz2 yz3
     xmm13 = zx0 zx1 zx2 zx3
     xmm14 = zy0 zy1 zy2 zy3
     xmm15 = zz0 zz1 zz2 zz3
     
     haddps xmm07 xmm08
         xmm07 = xx0+1 xx2+3 xy0+1 xy2+3
     haddps xmm09 xmm10
         xmm09 = xz0+1 xz2+3 yx0+1 yx2+3
     haddps xmm11 xmm12
         xmm11 = yy0+1 yy2+3 yz0+1 yz2+3
     haddps xmm13 xmm14
         xmm13 = zx0+1 zx2+3 zy0+1 zy2+3
     haddps xmm15 xmm14
         xmm15 = zz0+1 zz2+3 zy0+1 zy2+3
     
     haddps xmm07 xmm09
         xmm07 = xx0123 xy0123 xz0123 yx0123
     haddps xmm11 xmm13
         xmm11 = yy0123 yz0123 zx0123 zy0123
     haddps xmm15 xmm09
         xmm15 = zz0123 zy0123 xz0123 yx0123*/ 
    #ifdef __SSE3__
    xx = _mm_hadd_ps(xx,xy);
    xz = _mm_hadd_ps(xz,yx);
    yy = _mm_hadd_ps(yy,yz);
    zx = _mm_hadd_ps(zx,zy);
    zz = _mm_hadd_ps(zz,zy);

    xx = _mm_hadd_ps(xx,xz);
    yy = _mm_hadd_ps(yy,zx);
    zz = _mm_hadd_ps(zz,xz);
    #else
    // Emulate horizontal adds using UNPCKLPS/UNPCKHPS
    t0 = xx;
    t1 = xx;
    t0 = _mm_unpacklo_ps(t0,xz);
        // = xx0 xz0 xx1 xz1
    t1 = _mm_unpackhi_ps(t1,xz);
        // = xx2 xz2 xx3 xz3
    t0 = _mm_add_ps(t0,t1);
        // = xx02 xz02 xx13 xz13

    t1 = xy;
    t2 = xy;
    t1 = _mm_unpacklo_ps(t1,yx);
        // = xy0 yx0 xy1 yx1
    t2 = _mm_unpackhi_ps(t2,yx);
        // = xy2 yx2 xy3 yx3
    t1 = _mm_add_ps(t1,t2);
        // = xy02 yx02 xy13 yx13

    xx = t0;
    xx = _mm_unpacklo_ps(xx,t1);
        // = xx02 xy02 xz02 yx02
    t0 = _mm_unpackhi_ps(t0,t1);
        // = xx13 xy13 xz13 yx13
    xx = _mm_add_ps(xx,t0);
        // = xx0123 xy0123 xz0123 yx0123

    t0 = yy;
    t1 = yy;
    t0 = _mm_unpacklo_ps(t0,zx);
        // = yy0 zx0 yy1 zx1
    t1 = _mm_unpackhi_ps(t1,zx);
        // = yy2 zx2 yy3 zx3
    t0 = _mm_add_ps(t0,t1);
        // = yy02 zx02 yy13 zx13

    t1 = yz;
    t2 = yz;
    t1 = _mm_unpacklo_ps(t1,zy);
        // = yz0 zy0 yz1 zy1
    t2 = _mm_unpackhi_ps(t2,zy);
        // = yz2 zy2 yz3 zy3
    t1 = _mm_add_ps(t1,t2);
        // = yz02 zy02 yz13 zy13

    yy = t0;
    yy = _mm_unpacklo_ps(yy,t1);
        // = yy02 yz02 zx02 zy02
    t0 = _mm_unpackhi_ps(t0,t1);
        // = yy13 yz13 zx13 zy13
    yy = _mm_add_ps(yy,t0);
        // = yy0123 yz0123 zx0123 zy0123

    t1 = _mm_movehl_ps(t1,zz);
        // = zz2 zz3 - -
    zz = _mm_add_ps(zz,t1);
        // = zz02 zz13 - -
    t1 = _mm_shuffle_ps(zz,zz,_MM_SHUFFLE(1,1,1,1));
        // = zz13 zz13 zz13 zz13
    zz = _mm_add_ps(zz,t1);
        // = zz0123 zz1133 - -
    #endif

    _mm_store_ps(M  , xx);
    _mm_store_ps(M+4, yy);
    _mm_store_ps(M+8, zz);

    return rmsd2FromMandG(M,G_a,G_b,nrealatoms);
}