__m128 voodoo (__m128 a)
{
  __m128 x = insn_ABS (a), y = _mm_rsqrt_ps (x);
  y = _mm_add_ps (_mm_mul_ps (_mm_sub_ps (_mm_setzero_ps(), _mm_sub_ps (_mm_mul_ps (x, _mm_add_ps (_mm_mul_ps (y, y), _mm_setzero_ps())), v_one)), _mm_add_ps (_mm_mul_ps (y, v_half), _mm_setzero_ps())), y);
  return y;
}