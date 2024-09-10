void molec_quadrant_neighbor_interaction_fma(molec_Quadrant_t q, molec_Quadrant_t q_n, float* Epot_)
{
#ifdef __AVX2__
    const __m256 sigLJ = _mm256_set1_ps(molec_parameter->sigLJ);
    const __m256 epsLJ = _mm256_set1_ps(molec_parameter->epsLJ);

    const __m256 Rcut2 = _mm256_set1_ps(molec_parameter->Rcut2);

    const int N = q.N;
    const int N_n = q_n.N_pad;

    __m256 Epot8 = _mm256_setzero_ps();
    __m256 _1 = _mm256_set1_ps(1.f);
    __m256 _2 = _mm256_set1_ps(2.f);
    __m256 _24epsLJ = _mm256_mul_ps(_mm256_set1_ps(24.f), epsLJ);

    for(int i = 0; i < N; ++i)
    {
        const __m256 xi = _mm256_set1_ps(q.x[i]);
        const __m256 yi = _mm256_set1_ps(q.y[i]);
        const __m256 zi = _mm256_set1_ps(q.z[i]);

        __m256 f_xi = _mm256_setzero_ps();
        __m256 f_yi = _mm256_setzero_ps();
        __m256 f_zi = _mm256_setzero_ps();

        for(int j = 0; j < N_n; j += 8)
        {
            // count number of interactions
            if(MOLEC_CELLLIST_COUNT_INTERACTION)
                ++num_potential_interactions;

            // load coordinates and fores into AVX vectors
            const __m256 xj = _mm256_load_ps(&q_n.x[j]);
            const __m256 yj = _mm256_load_ps(&q_n.y[j]);
            const __m256 zj = _mm256_load_ps(&q_n.z[j]);

            __m256 f_xj = _mm256_load_ps(&q_n.f_x[j]);
            __m256 f_yj = _mm256_load_ps(&q_n.f_y[j]);
            __m256 f_zj = _mm256_load_ps(&q_n.f_z[j]);


            // distance computation
            const __m256 xij = _mm256_sub_ps(xi, xj);
            const __m256 yij = _mm256_sub_ps(yi, yj);
            const __m256 zij = _mm256_sub_ps(zi, zj);


            const __m256 zij2 = _mm256_mul_ps(zij, zij);
            const __m256 r2 = _mm256_fmadd_ps(xij, xij, _mm256_fmadd_ps(yij, yij, zij2));


            // r2 < Rcut2
            const __m256 mask = _mm256_cmp_ps(r2, Rcut2, _CMP_LT_OQ);

            // if( any(r2 < R2) )
            if(_mm256_movemask_ps(mask))
            {
                const __m256 r2inv = _mm256_div_ps(_1, r2);

                const __m256 s2 = _mm256_mul_ps(_mm256_mul_ps(sigLJ, sigLJ), r2inv);
                const __m256 s6 = _mm256_mul_ps(_mm256_mul_ps(s2, s2), s2);
                const __m256 s12 = _mm256_mul_ps(s6, s6);

                const __m256 s12_minus_s6 = _mm256_sub_ps(s12, s6);
                const __m256 two_s12_minus_s6 = _mm256_sub_ps(_mm256_mul_ps(_2, s12), s6);

                Epot8 = _mm256_add_ps(Epot8, _mm256_and_ps(s12_minus_s6, mask));

                const __m256 fr = _mm256_mul_ps(_mm256_mul_ps(_24epsLJ, r2inv), two_s12_minus_s6);
                const __m256 fr_mask = _mm256_and_ps(fr, mask);


                // update forces
                f_xi = _mm256_fmadd_ps(fr_mask, xij,f_xi);
                f_yi = _mm256_fmadd_ps(fr_mask, yij,f_yi);
                f_zi = _mm256_fmadd_ps(fr_mask, zij,f_zi);

                f_xj = _mm256_fnmadd_ps(fr_mask,xij,f_xj);
                f_yj = _mm256_fnmadd_ps(fr_mask,yij,f_yj);
                f_zj = _mm256_fnmadd_ps(fr_mask,zij,f_zj);

                // store back j-forces
                _mm256_store_ps(&q_n.f_x[j], f_xj);
                _mm256_store_ps(&q_n.f_y[j], f_yj);
                _mm256_store_ps(&q_n.f_z[j], f_zj);
            }
        }

        // update i-forces
        float MOLEC_ALIGNAS(32) f_array[8];
        _mm256_store_ps(f_array, f_xi);
        q.f_x[i] += f_array[0] + f_array[1] + f_array[2] + f_array[3] + f_array[4] + f_array[5]
                    + f_array[6] + f_array[7];
        _mm256_store_ps(f_array, f_yi);
        q.f_y[i] += f_array[0] + f_array[1] + f_array[2] + f_array[3] + f_array[4] + f_array[5]
                    + f_array[6] + f_array[7];
        _mm256_store_ps(f_array, f_zi);
        q.f_z[i] += f_array[0] + f_array[1] + f_array[2] + f_array[3] + f_array[4] + f_array[5]
                    + f_array[6] + f_array[7];
    }

    float MOLEC_ALIGNAS(32) E_pot_array[8];
    _mm256_store_ps(E_pot_array, Epot8);

    // perform reduction of potential energy
    *Epot_ += 4
              * molec_parameter->epsLJ*(E_pot_array[0] + E_pot_array[1] + E_pot_array[2]
                                        + E_pot_array[3] + E_pot_array[4] + E_pot_array[5]
                                        + E_pot_array[6] + E_pot_array[7]);
#endif
}