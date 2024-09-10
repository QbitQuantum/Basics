void static
xop_test ()
{
    int i;
    union128  source1, source2, u;
    union128i_d source3;
    float s1[4] = {1, 2, 3, 4};
    float s2[4] = {5, 6, 7, 8};
    int   s3[4] = {0, 1, 0, 1};
    float e[4];

    source1.x = _mm_loadu_ps(s1);
    source2.x = _mm_loadu_ps(s2);
    source3.x = _mm_loadu_si128((__m128i*) s3);
    u.x = _mm_permute2_ps(source1.x, source2.x, source3.x, ZERO_MATCH);

    for (i = 0; i < 4; ++i) {
        e[i] = sel_and_condzerosp(&s1[i & 0x4], &s2[i & 0x4], s3[i] & 0xf, ZERO_MATCH & 0x3);
    }

    if (check_union128 (u, e))
      abort ();
}