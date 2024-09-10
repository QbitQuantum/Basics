void static
TEST (void)
{
    __m128i src, mask;
    char s[16] = { 1,-2,3,-4,5,-6,7,-8,9,-10,11,-12,13,-14,15,-16 };
    char m[16];

    char u[20] = { 0 };
    int i;

    for (i = 0; i < 16; i++)
        m[i] = mask_v (i);

    src = _mm_loadu_si128 ((__m128i *)s);
    mask = _mm_loadu_si128 ((__m128i *)m);

    _mm_maskmoveu_si128 (src, mask, u+3);

    for (i = 0; i < 16; i++)
        if (u[i+3] != (m[i] ? s[i] : 0))
            abort ();
}