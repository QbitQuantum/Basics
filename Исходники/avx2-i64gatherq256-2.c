void static
avx2_test (void)
{
    long long i;
    union256i_q idx;
    union256i_q res;
    long long s1[4], res_ref[4] = { 0 };

    for (i = 0; i < 4; ++i)
    {
        /* Set some stuff */
        s1[i] = 1983 * (i + 1) * (i + 2);

        /* About to gather in reverse order,
           divide by 2 to demonstrate scale */
        idx.a[i] = (32 - (i + 1) * 8) >> 1;
    }

    res.x = _mm256_i64gather_epi64 ((long long int *) s1, idx.x, 2);

    compute_i64gatherq256 (s1, idx.a, 2, res_ref);

    if (check_union256i_q (res, res_ref) != 0)
        abort ();
}