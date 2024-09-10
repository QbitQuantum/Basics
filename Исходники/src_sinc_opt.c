static inline __m128 horizontal_add(const __m128 a)
{
#if 0 //!! needs SSE3
    const __m128 ftemp = _mm_hadd_ps(a, a);
    return _mm_hadd_ps(ftemp, ftemp);
#else    
    const __m128 ftemp = _mm_add_ps(a, _mm_movehl_ps(a, a)); //a0+a2,a1+a3
    return _mm_add_ss(ftemp, _mm_shuffle_ps(ftemp, ftemp, _MM_SHUFFLE(1, 1, 1, 1))); //(a0+a2)+(a1+a3)
#endif
}