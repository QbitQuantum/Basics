const ALfloat *Resample_lerp32_SSE2(const BsincState* UNUSED(state), const ALfloat *src, ALuint frac, ALuint increment,
                                    ALfloat *restrict dst, ALuint numsamples)
{
    const __m128i increment4 = _mm_set1_epi32(increment*4);
    const __m128 fracOne4 = _mm_set1_ps(1.0f/FRACTIONONE);
    const __m128i fracMask4 = _mm_set1_epi32(FRACTIONMASK);
    alignas(16) union { ALuint i[4]; float f[4]; } pos_;
    alignas(16) union { ALuint i[4]; float f[4]; } frac_;
    __m128i frac4, pos4;
    ALuint pos;
    ALuint i;

    InitiatePositionArrays(frac, increment, frac_.i, pos_.i, 4);

    frac4 = _mm_castps_si128(_mm_load_ps(frac_.f));
    pos4 = _mm_castps_si128(_mm_load_ps(pos_.f));

    for(i = 0;numsamples-i > 3;i += 4)
    {
        const __m128 val1 = _mm_setr_ps(src[pos_.i[0]], src[pos_.i[1]], src[pos_.i[2]], src[pos_.i[3]]);
        const __m128 val2 = _mm_setr_ps(src[pos_.i[0]+1], src[pos_.i[1]+1], src[pos_.i[2]+1], src[pos_.i[3]+1]);

        /* val1 + (val2-val1)*mu */
        const __m128 r0 = _mm_sub_ps(val2, val1);
        const __m128 mu = _mm_mul_ps(_mm_cvtepi32_ps(frac4), fracOne4);
        const __m128 out = _mm_add_ps(val1, _mm_mul_ps(mu, r0));

        _mm_store_ps(&dst[i], out);

        frac4 = _mm_add_epi32(frac4, increment4);