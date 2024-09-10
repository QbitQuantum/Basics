// ---------- local operators and operator-wrappers ----------
UNUSED static inline __m128
local_add_ps ( __m128 in1, __m128 in2 )
{
    return _mm_add_ps ( in1, in2 );
}