__m128
t2(__m128 a, __m128 b)
{
a=_mm_sqrt_ps(a);
b=_mm_sqrt_ps(b);
return _mm_andnot_ps (a,b);
}