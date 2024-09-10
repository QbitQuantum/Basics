__m128i
t2(void)
{
return _mm_andnot_si128 (magic_a,magic_b);
}