DBL AVXFMA4Noise(const Vector3d& EPoint, int noise_generator)
{
    DBL x, y, z;
    DBL *mp;
    int ix, iy, iz;
    int ixiy_hash, ixjy_hash, jxiy_hash, jxjy_hash;
    DBL sum;

    // TODO FIXME - global statistics reference
    // Stats[Calls_To_Noise]++;

    if (noise_generator==kNoiseGen_Perlin)
    {
        // The 1.59 and 0.985 are to correct for some biasing problems with
        // the random # generator used to create the noise tables.  Final
        // range of values is about 5.0e-4 below 0.0 and above 1.0.  Mean
        // value is 0.49 (ideally it would be 0.5).
        sum = 0.5 * (1.59 * SolidNoise(EPoint) + 0.985);

        // Clamp final value to 0-1 range
            if (sum < 0.0) sum = 0.0;
            if (sum > 1.0) sum = 1.0;

        return sum;
    }

    x = EPoint[X];
    y = EPoint[Y];
    z = EPoint[Z];

    /* its equivalent integer lattice point. */
    /* ix = (int)x; iy = (int)y; iz = (long)z; */
    /* JB fix for the range problem */

    __m128d xy = _mm_setr_pd(x, y);
    __m128d zn = _mm_set_sd(z);
    __m128d epsy = _mm_set1_pd(1.0 - EPSILON);
    __m128d xy_e = _mm_sub_pd(xy, epsy);
    __m128d zn_e = _mm_sub_sd(zn, epsy);
    __m128i tmp_xy = _mm_cvttpd_epi32(_mm_blendv_pd(xy, xy_e, xy));
    __m128i tmp_zn = _mm_cvttpd_epi32(_mm_blendv_pd(zn, zn_e, zn));

    __m128i noise_min_xy = _mm_setr_epi32(NOISE_MINX, NOISE_MINY, 0, 0);
    __m128i noise_min_zn = _mm_set1_epi32(NOISE_MINZ);

    __m128d xy_ixy = _mm_sub_pd(xy, _mm_cvtepi32_pd(tmp_xy));
    __m128d zn_izn = _mm_sub_sd(zn, _mm_cvtepi32_pd(tmp_zn));

    const __m128i fff = _mm_set1_epi32(0xfff);
    __m128i i_xy = _mm_and_si128(_mm_sub_epi32(tmp_xy, noise_min_xy), fff);
    __m128i i_zn = _mm_and_si128(_mm_sub_epi32(tmp_zn, noise_min_zn), fff);

    ix = _mm_extract_epi32(i_xy, 0);
    iy = _mm_extract_epi32(i_xy, 1);
    iz = _mm_extract_epi32(i_zn, 0);

    ixiy_hash = Hash2d(ix, iy);
    jxiy_hash = Hash2d(ix + 1, iy);
    ixjy_hash = Hash2d(ix, iy + 1);
    jxjy_hash = Hash2d(ix + 1, iy + 1);

    mp = &RTable[Hash1dRTableIndex(ixiy_hash, iz)];
    DBL *mp2 = &RTable[Hash1dRTableIndex(ixjy_hash, iz)];
    DBL *mp3 = &RTable[Hash1dRTableIndex(ixiy_hash, iz + 1)];
    DBL *mp4 = &RTable[Hash1dRTableIndex(ixjy_hash, iz + 1)];
    DBL *mp5 = &RTable[Hash1dRTableIndex(jxiy_hash, iz)];
    DBL *mp6 = &RTable[Hash1dRTableIndex(jxjy_hash, iz)];
    DBL *mp7 = &RTable[Hash1dRTableIndex(jxiy_hash, iz + 1)];
    DBL *mp8 = &RTable[Hash1dRTableIndex(jxjy_hash, iz + 1)];

    const __m128d three = _mm_set1_pd(3.0);
    const __m128d two = _mm_set1_pd(2.0);
    const __m128d one = _mm_set1_pd(1.0);

    __m128d ix_mm = _mm_unpacklo_pd(xy_ixy, xy_ixy);
    __m128d iy_mm = _mm_unpackhi_pd(xy_ixy, xy_ixy);
    __m128d iz_mm = _mm_unpacklo_pd(zn_izn, zn_izn);

    __m128d jx_mm = _mm_sub_pd(ix_mm, one);
    __m128d jy_mm = _mm_sub_pd(iy_mm, one);
    __m128d jz_mm = _mm_sub_pd(iz_mm, one);

    __m128d mm_sxy = _mm_mul_pd(_mm_mul_pd(xy_ixy, xy_ixy), _mm_nmacc_pd(two, xy_ixy, three));
    __m128d mm_sz = _mm_mul_pd(_mm_mul_pd(iz_mm, iz_mm), _mm_nmacc_pd(two, iz_mm, three));

    __m128d mm_tz = _mm_sub_pd(one, mm_sz);
    __m128d mm_txy = _mm_sub_pd(one, mm_sxy);
    __m128d mm_tysy = _mm_unpackhi_pd(mm_txy, mm_sxy);
    __m128d mm_txty_txsy = _mm_mul_pd(_mm_unpacklo_pd(mm_txy, mm_txy), mm_tysy);
    __m128d mm_sxty_sxsy = _mm_mul_pd(_mm_unpacklo_pd(mm_sxy, mm_sxy), mm_tysy);

    __m128d y_mm = _mm_unpacklo_pd(iy_mm, jy_mm);

    __m128d mp_t1, mp_t2, mp1_mm, mp2_mm, mp4_mm, mp6_mm, sum_p, s_mm;
    __m128d int_sum1 = _mm_setzero_pd();

    s_mm = _mm_mul_pd(mm_txty_txsy, mm_tz);
    INCRSUMP2(mp, mp2, s_mm, ix_mm, y_mm, iz_mm, int_sum1);

    s_mm = _mm_mul_pd(mm_txty_txsy, mm_sz);
    INCRSUMP2(mp3, mp4, s_mm, ix_mm, y_mm, jz_mm, int_sum1);

    s_mm = _mm_mul_pd(mm_sxty_sxsy, mm_tz);
    INCRSUMP2(mp5, mp6, s_mm, jx_mm, y_mm, iz_mm, int_sum1);

    s_mm = _mm_mul_pd(mm_sxty_sxsy, mm_sz);
    INCRSUMP2(mp7, mp8, s_mm, jx_mm, y_mm, jz_mm, int_sum1);

    int_sum1 = _mm_hadd_pd(int_sum1, int_sum1);

    if(noise_generator==kNoiseGen_RangeCorrected)
    {
        /* details of range here:
        Min, max: -1.05242, 0.988997
        Mean: -0.0191481, Median: -0.535493, Std Dev: 0.256828

        We want to change it to as close to [0,1] as possible.
        */
        const __m128d r2 = _mm_set_sd(0.48985582);
        const __m128d r1r2 = _mm_set_sd(1.05242*0.48985582);
        int_sum1 = _mm_macc_sd(int_sum1, r2, r1r2);
    }
    else
    {
        int_sum1 = _mm_add_sd(int_sum1, _mm_set_sd(0.5));
    }

    int_sum1 = _mm_min_sd(one, int_sum1);
    int_sum1 = _mm_max_sd(_mm_setzero_pd(), int_sum1);
    _mm_store_sd(&sum, int_sum1);

    return (sum);
}