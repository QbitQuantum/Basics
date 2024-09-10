extern void
baseInputs(const TanBoard anBoard, float arInput[])
{
    int i = 3;

    const unsigned int *pB = &anBoard[0][0];
    float *pInput = &arInput[0];
    register __m128 vec0;
    register __m128 vec1;
    register __m128 vec2;
    register __m128 vec3;
    register __m128 vec4;
    register __m128 vec5;
    register __m128 vec6;
    register __m128 vec7;

    while (i--) {
        vec0 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput, vec0);
        vec1 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec1);
        vec2 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec2);
        vec3 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec3);
        vec4 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec4);
        vec5 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec5);
        vec6 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec6);
        vec7 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec7);
        pInput += 4;
    }

    /* bar */
    vec0 = _mm_load_ps(inpvecb[*pB++]);
    _mm_store_ps(pInput, vec0);
    pInput += 4;

    i = 3;
    while (i--) {
        vec0 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput, vec0);
        vec1 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec1);
        vec2 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec2);
        vec3 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec3);
        vec4 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec4);
        vec5 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec5);
        vec6 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec6);
        vec7 = _mm_load_ps(inpvec[*pB++]);
        _mm_store_ps(pInput += 4, vec7);
        pInput += 4;
    }

    /* bar */
    vec0 = _mm_load_ps(inpvecb[*pB]);
    _mm_store_ps(pInput, vec0);

#if defined(USE_AVX)
    _mm256_zeroupper();
#endif

    return;
}