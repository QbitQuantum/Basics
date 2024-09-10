static void
sha_test (void)
{
    union128i_d s1, s2, res;
    int res_ref[4];

    s1.x = _mm_set_epi32 (111, 0, 0, 0);
    s2.x = _mm_set_epi32 (222, 333, 444, 555);

    res.x = _mm_sha1nexte_epu32 (s1.x, s2.x);

    compute_sha1nexte (s1.a, s2.a, res_ref);

    if (check_union128i_d (res, res_ref))
        abort ();
}