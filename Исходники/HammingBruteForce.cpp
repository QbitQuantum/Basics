void HammingBruteForce::match_all(const int64_t *a, int n_a, const int64_t *b, int n_b) {
    std::fill(index_ab, index_ab + n_a, -1);
    std::fill(distance_ab, distance_ab + n_a, threshold);
    for (int i = 0; i < n_a; i++) {
        for (int j = 0; j < n_b; j++) {
            int d_ab0 = _mm_popcnt_u64(a[i*4 + 0] ^ b[j*4 + 0]);
            int d_ab1 = _mm_popcnt_u64(a[i*4 + 1] ^ b[j*4 + 1]);
            int d_ab2 = _mm_popcnt_u64(a[i*4 + 2] ^ b[j*4 + 2]);
            int d_ab3 = _mm_popcnt_u64(a[i*4 + 3] ^ b[j*4 + 3]);
            int d_ab = d_ab0 + d_ab1 + d_ab2 + d_ab3;

            int is_closer = d_ab < distance_ab[i];
            index_ab[i] = is_closer ? j : index_ab[i];
            distance_ab[i] = is_closer ? d_ab : distance_ab[i];
        }
    }
}