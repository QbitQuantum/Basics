void static
avx_test (void)
{
    int i;
    int m[8] = {mask_v(0), mask_v(1), mask_v(2), mask_v(3), mask_v(4), mask_v(5), mask_v(6), mask_v(7)};
    float s[8] = {1,2,3,4,5,6,7,8};
    union256 src, mask;
    float e [8] = {0.0};
    float d [8] = {0.0};

    src.x = _mm256_loadu_ps (s);
    mask.x = _mm256_loadu_ps ((float *)m);
    _mm256_maskstore_ps (d, mask.x, src.x);

    for (i = 0 ; i < 8; i++)
        e[i] = m[i] ? s[i] : 0;

    if (checkVf (d, e, 8))
        abort ();
}