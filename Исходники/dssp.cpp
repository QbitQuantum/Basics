/**
 * Identify bends in the chain, where the kappa angle (virtual bond angle from
 * c-alpha i-2, to i, to i+2) is greater than 70 degrees
 * dssp-2.2.0/structure.cpp:1729
 */
static std::vector<int> calculate_bends(const float* xyz, const int* ca_indices,
    const int* chain_ids, const int n_residues, std::vector<int>& skip)
{
    __m128 prev_ca, this_ca, next_ca, u_prime, v_prime, u, v;
    float kappa;
    std::vector<int> is_bend(n_residues, 0);
    for (int i = 2; i < n_residues-2; i++) {
        if (chain_ids[i-2] == chain_ids[i+2] && !skip[i-2] && !skip[i] && !skip[i+2]) {
            prev_ca = load_float3(xyz + 3*ca_indices[i-2]);
            this_ca = load_float3(xyz + 3*ca_indices[i]);
            next_ca = load_float3(xyz + 3*ca_indices[i+2]);
            u_prime = _mm_sub_ps(prev_ca, this_ca);
            v_prime = _mm_sub_ps(this_ca, next_ca);
            /* normalize the vectors u_prime and v_prime */
            u = _mm_div_ps(u_prime, _mm_sqrt_ps(_mm_dp_ps2(u_prime, u_prime, 0x7F)));
            v = _mm_div_ps(v_prime, _mm_sqrt_ps(_mm_dp_ps2(v_prime, v_prime, 0x7F)));
            /* compute the arccos of the dot product. this gives the angle */
            kappa = (float) acos(CLIP(_mm_cvtss_f32(_mm_dp_ps2(u, v, 0x71)), -1, 1));
            is_bend[i] = kappa > (70 * (M_PI / 180.0));
        }
    }
    return is_bend;
}