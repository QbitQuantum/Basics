static void
sse3_test_hsubpd_subsume (double *i1, double *i2, double *r)
{
    __m128d t1 = _mm_load_pd (i1);
    __m128d t2 = _mm_load_pd (i2);

    t1 = _mm_hsub_pd (t1, t2);

    _mm_storeu_pd (r, t1);
}