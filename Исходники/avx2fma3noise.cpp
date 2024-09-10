DBL AVX2FMA3Noise(const Vector3d& EPoint, int noise_generator)
{
    AVX2TABLETYPE *mp;
    DBL sum = 0.0;

    // TODO FIXME - global statistics reference
    // Stats[Calls_To_Noise]++;

    if (noise_generator == kNoiseGen_Perlin)
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

    const __m256d ONE_PD = _mm256_set1_pd(1);
    const __m128i short_si128 = _mm_set1_epi32(0xffff);

    const __m256d xyzn = _mm256_setr_pd(EPoint[X], EPoint[Y], EPoint[Z], 0);
    const __m256d epsy = _mm256_set1_pd(1.0 - EPSILON);
    const __m256d xyzn_e = _mm256_sub_pd(xyzn, epsy);
    const __m128i tmp_xyzn = _mm256_cvttpd_epi32(_mm256_blendv_pd(xyzn, xyzn_e, xyzn));

    const __m128i noise_min_xyzn = _mm_setr_epi32(NOISE_MINX, NOISE_MINY, NOISE_MINZ, 0);

    const __m256d xyz_ixyzn = _mm256_sub_pd(xyzn, _mm256_cvtepi32_pd(tmp_xyzn));
    const __m256d xyz_jxyzn = _mm256_sub_pd(xyz_ixyzn, ONE_PD);

    const __m128i i_xyzn = _mm_and_si128(_mm_sub_epi32(tmp_xyzn, noise_min_xyzn),
        _mm_set1_epi32(0xfff));

    const __m256d s_xyzn = _mm256_mul_pd(xyz_ixyzn,
        _mm256_mul_pd(xyz_ixyzn,
            _mm256_sub_pd(_mm256_set1_pd(3.0),
                _mm256_add_pd(xyz_ixyzn, xyz_ixyzn))));

    const __m256d t_xyzn = _mm256_sub_pd(ONE_PD, s_xyzn);

    const __m256d txtysxsy = _mm256_permute2f128_pd(t_xyzn, s_xyzn, 0x20);
    const __m256d txsxtxsx = PERMUTE4x64(txtysxsy, _MM_SHUFFLE(2, 0, 2, 0));
    const __m256d tytysysy = PERMUTE4x64(txtysxsy, _MM_SHUFFLE(3, 3, 1, 1));

    const __m256d txtysxtytxsysxsy = _mm256_mul_pd(txsxtxsx, tytysysy);

    const __m256d incrsump_s1 = _mm256_mul_pd(txtysxtytxsysxsy, PERMUTE4x64(t_xyzn, _MM_SHUFFLE(2, 2, 2, 2)));
    const __m256d incrsump_s2 = _mm256_mul_pd(txtysxtytxsysxsy, PERMUTE4x64(s_xyzn, _MM_SHUFFLE(2, 2, 2, 2)));

    int ints[4];
    _mm_storeu_si128((__m128i*)(ints), i_xyzn);

    const int ixiy_hash = Hash2d(ints[0], ints[1]);
    const int jxiy_hash = Hash2d(ints[0] + 1, ints[1]);
    const int ixjy_hash = Hash2d(ints[0], ints[1] + 1);
    const int jxjy_hash = Hash2d(ints[0] + 1, ints[1] + 1);

    const int iz = ints[2];

    const __m256d iii = _mm256_blend_pd(PERMUTE4x64(xyz_ixyzn, _MM_SHUFFLE(2, 1, 0, 0)), _mm256_set_pd(0, 0, 0, 0.5), 0x1);
    const __m256d jjj = _mm256_blend_pd(PERMUTE4x64(xyz_jxyzn, _MM_SHUFFLE(2, 1, 0, 0)), _mm256_set_pd(0, 0, 0, 0.5), 0x1);

    __m256d sumr = _mm256_setzero_pd();
    __m256d sumr1 = _mm256_setzero_pd();


    mp = &AVX2RTable[Hash1dRTableIndexAVX(ixiy_hash, iz)];
    INCSUMAVX_NOBLEND(sumr, mp, PERMUTE4x64(incrsump_s1, _MM_SHUFFLE(0, 0, 0, 0)), iii);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(jxiy_hash, iz)];
    INCSUMAVX(sumr1, mp, PERMUTE4x64(incrsump_s1, _MM_SHUFFLE(1, 1, 1, 1)), iii, jjj, 2);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(ixjy_hash, iz)];
    INCSUMAVX(sumr, mp, PERMUTE4x64(incrsump_s1, _MM_SHUFFLE(2, 2, 2, 2)), iii, jjj, 4);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(jxjy_hash, iz)];
    INCSUMAVX(sumr1, mp, PERMUTE4x64(incrsump_s1, _MM_SHUFFLE(3, 3, 3, 3)), iii, jjj, 6);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(ixiy_hash, iz + 1)];
    INCSUMAVX(sumr, mp, PERMUTE4x64(incrsump_s2, _MM_SHUFFLE(0, 0, 0, 0)), iii, jjj, 8);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(jxiy_hash, iz + 1)];
    INCSUMAVX(sumr1, mp, PERMUTE4x64(incrsump_s2, _MM_SHUFFLE(1, 1, 1, 1)), iii, jjj, 10);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(ixjy_hash, iz + 1)];
    INCSUMAVX(sumr, mp, PERMUTE4x64(incrsump_s2, _MM_SHUFFLE(2, 2, 2, 2)), iii, jjj, 12);

    mp = &AVX2RTable[Hash1dRTableIndexAVX(jxjy_hash, iz + 1)];
    INCSUMAVX_NOBLEND(sumr1, mp, PERMUTE4x64(incrsump_s2, _MM_SHUFFLE(3, 3, 3, 3)), jjj);

    {
        sumr = _mm256_add_pd(sumr, sumr1);

        __m128d sumr_up = _mm256_extractf128_pd(sumr,1);
        sumr_up = _mm_add_pd(_mm256_castpd256_pd128(sumr),sumr_up);
        sumr_up = _mm_hadd_pd(sumr_up,sumr_up);
        sum = _mm_cvtsd_f64(sumr_up);
    }

    if (noise_generator == kNoiseGen_RangeCorrected)
    {
        /* details of range here:
        Min, max: -1.05242, 0.988997
        Mean: -0.0191481, Median: -0.535493, Std Dev: 0.256828

        We want to change it to as close to [0,1] as possible.
        */
        sum += 1.05242;
        sum *= 0.48985582;
        /*sum *= 0.5;
        sum += 0.5;*/

        if (sum < 0.0)
            sum = 0.0;
        if (sum > 1.0)
            sum = 1.0;
    }
    else
    {
        sum = sum + 0.5;                     /* range at this point -0.5 - 0.5... */

        if (sum < 0.0)
            sum = 0.0;
        if (sum > 1.0)
            sum = 1.0;
    }



#if CHECK_FUNCTIONAL
    {
        DBL orig_sum = PortableNoise(EPoint, noise_generator);
        if (fabs(orig_sum - sum) >= EPSILON)
        {
            throw POV_EXCEPTION_STRING("Noise error");
        }

    }

#endif

    _mm256_zeroupper();
    return (sum);
}