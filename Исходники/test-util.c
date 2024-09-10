static void
check_bitwise_is_all_zeros(void)
{
    int n_loops;

    n_loops = 0;
    for (n_loops = 0; n_loops < 100; n_loops++) {
        ovs_be64 x = htonll(0);
        int i;

        for (i = 0; i < 64; i++) {
            ovs_be64 bit;
            int ofs, n;

            /* Change a random 0-bit into a 1-bit. */
            do {
                bit = htonll(UINT64_C(1) << (random_uint32() % 64));
            } while (x & bit);
            x |= bit;

            for (ofs = 0; ofs < 64; ofs++) {
                for (n = 0; n <= 64 - ofs; n++) {
                    bool expect;
                    bool answer;

                    expect = (n == 64
                              ? x == 0
                              : !(x & htonll(((UINT64_C(1) << n) - 1)
                                             << ofs)));
                    answer = bitwise_is_all_zeros(&x, sizeof x, ofs, n);
                    if (expect != answer) {
                        fprintf(stderr,
                                "bitwise_is_all_zeros(0x%016"PRIx64",8,%d,%d "
                                "returned %s instead of %s\n",
                                ntohll(x), ofs, n,
                                answer ? "true" : "false",
                                expect ? "true" : "false");
                        abort();
                    }
                }
            }
        }
    }
}