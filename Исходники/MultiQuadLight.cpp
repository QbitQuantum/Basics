static inline float rsqrt_fast(const float x)
{
  const __m128 a = _mm_set_ss(x);
  const __m128 r = _mm_rsqrt_ps(a);
  return _mm_cvtss_f32(r);
}