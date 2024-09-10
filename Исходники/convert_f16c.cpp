static __forceinline void
convert_float_to_half(uint8_t* dstp, const float* srcp, size_t count)
{
    for (size_t x = 0; x < count; x += 8) {
        __m256 s = _mm256_load_ps(srcp + x);
        __m128i d = _mm256_cvtps_ph(s, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
        _mm_stream_si128(reinterpret_cast<__m128i*>(dstp + 2 * x), d);
    }
}