static __m128i cielabv (union hvrgbpix rgb)
{
    __m128 xvxyz[2] = {_mm_set1_ps(0.5),_mm_set1_ps(0.5) }; //,0.5,0.5,0.5);

    __m128 vcam0 = _mm_setr_ps(cielab_xyz_cam[0][0],cielab_xyz_cam[1][0],cielab_xyz_cam[2][0],0);
    __m128 vcam1 = _mm_setr_ps(cielab_xyz_cam[0][1],cielab_xyz_cam[1][1],cielab_xyz_cam[2][1],0);
    __m128 vcam2 = _mm_setr_ps(cielab_xyz_cam[0][2],cielab_xyz_cam[1][2],cielab_xyz_cam[2][2],0);
    __m128 vrgb0h = _mm_set1_ps(rgb.h.c[0]);
    __m128 vrgb1h = _mm_set1_ps(rgb.h.c[1]);
    __m128 vrgb2h = _mm_set1_ps(rgb.h.c[2]);
    __m128 vrgb0v = _mm_set1_ps(rgb.v.c[0]);
    __m128 vrgb1v = _mm_set1_ps(rgb.v.c[1]);
    __m128 vrgb2v = _mm_set1_ps(rgb.v.c[2]);

    xvxyz[0] = _mm_add_ps(xvxyz[0], _mm_mul_ps(vcam0,vrgb0h));
    xvxyz[0] = _mm_add_ps(xvxyz[0], _mm_mul_ps(vcam1,vrgb1h));
    xvxyz[0] = _mm_add_ps(xvxyz[0], _mm_mul_ps(vcam2,vrgb2h));
    xvxyz[1] = _mm_add_ps(xvxyz[1], _mm_mul_ps(vcam0,vrgb0v));
    xvxyz[1] = _mm_add_ps(xvxyz[1], _mm_mul_ps(vcam1,vrgb1v));
    xvxyz[1] = _mm_add_ps(xvxyz[1], _mm_mul_ps(vcam2,vrgb2v));

    xvxyz[0] = _mm_max_ps(_mm_set1_ps(0),
                          _mm_min_ps(_mm_set1_ps(0xffff),
                                     _mm_round_ps(xvxyz[0], _MM_FROUND_TO_ZERO)));
    xvxyz[1] = _mm_max_ps(_mm_set1_ps(0),
                          _mm_min_ps(_mm_set1_ps(0xffff),
                                     _mm_round_ps(xvxyz[1], _MM_FROUND_TO_ZERO)));
    __m128i loadaddrh = _mm_cvttps_epi32(xvxyz[0]);
    __m128i loadaddrv = _mm_cvttps_epi32(xvxyz[1]);
#ifdef __AVX__
    __m256 vlab,
           vxyz = { cielab_cbrt[_mm_extract_epi32(loadaddrh,1)],
                    cielab_cbrt[_mm_extract_epi32(loadaddrh,0)],
                    cielab_cbrt[_mm_extract_epi32(loadaddrh,1)],
                    0,
                    cielab_cbrt[_mm_extract_epi32(loadaddrv,1)],
                    cielab_cbrt[_mm_extract_epi32(loadaddrv,0)],
                    cielab_cbrt[_mm_extract_epi32(loadaddrv,1)],
                    0},
           vxyz2 =  {0,
                     cielab_cbrt[_mm_extract_epi32(loadaddrh,1)],
                     cielab_cbrt[_mm_extract_epi32(loadaddrh,2)],
                     cielab_cbrt[_mm_extract_epi32(loadaddrh,0)],
                     0,
                     cielab_cbrt[_mm_extract_epi32(loadaddrv,1)],
                     cielab_cbrt[_mm_extract_epi32(loadaddrv,2)],
                     cielab_cbrt[_mm_extract_epi32(loadaddrv,0)]};

    vlab = _mm256_sub_ps(vxyz,vxyz2);
    vlab = _mm256_mul_ps(vlab, _mm256_setr_ps(116,500,200,0,116,500,200,0));
    vlab = _mm256_sub_ps(vlab, _mm256_setr_ps(16,0,0,0,16,0,0,0));
    vlab = _mm256_mul_ps(vlab,_mm256_set1_ps(64));
    vlab = _mm256_round_ps(vlab, _MM_FROUND_TO_ZERO);
    __m256i vlabi = _mm256_cvtps_epi32(vlab);
    return _mm_packs_epi32(_mm256_castsi256_si128(vlabi), ((__m128i*)&vlabi)[1]);
#else
    __m128 vlabh, vxyzh = {cielab_cbrt[_mm_extract_epi32(loadaddrh,0)],
                           cielab_cbrt[_mm_extract_epi32(loadaddrh,1)],
                           cielab_cbrt[_mm_extract_epi32(loadaddrh,2)],
                           0};
    __m128 vlabv, vxyzv = {cielab_cbrt[_mm_extract_epi32(loadaddrv,0)],
                           cielab_cbrt[_mm_extract_epi32(loadaddrv,1)],
                           cielab_cbrt[_mm_extract_epi32(loadaddrv,2)],
                           0};

    vlabh = _mm_sub_ps(_mm_shuffle_ps(vxyzh,vxyzh,_MM_SHUFFLE(0,1,0,1)),
                       _mm_shuffle_ps(vxyzh,vxyzh,_MM_SHUFFLE(0,2,1,3)));
    vlabh = _mm_mul_ps(vlabh,_mm_setr_ps(116,500,200,0));
    vlabh = _mm_sub_ps(vlabh,_mm_setr_ps(16,0,0,0));
    vlabh = _mm_mul_ps(vlabh,_mm_set_ps1(64));
    vlabh = _mm_round_ps(vlabh, _MM_FROUND_TO_ZERO);

    vlabv = _mm_sub_ps(_mm_shuffle_ps(vxyzv,vxyzv,_MM_SHUFFLE(0,1,0,1)),
                       _mm_shuffle_ps(vxyzv,vxyzv,_MM_SHUFFLE(0,2,1,3)));
    vlabv = _mm_mul_ps(vlabv,_mm_setr_ps(116,500,200,0));
    vlabv = _mm_sub_ps(vlabv,_mm_setr_ps(16,0,0,0));
    vlabv = _mm_mul_ps(vlabv,_mm_set_ps1(64));
    vlabv = _mm_round_ps(vlabv, _MM_FROUND_TO_ZERO);

    return _mm_set_epi64(_mm_cvtps_pi16(vlabv),_mm_cvtps_pi16(vlabh));
#endif
}