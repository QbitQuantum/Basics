irreg_poly_area_func_sign(double, _avx) {
    if (__builtin_expect(is_null(cords) || cords_len == 0, 0))
        return 0;

    __m256d
        curr,
        forw,
        coef_0,
        coef_1,
        end = _mm256_load_pd((const double *)cords),
        accum_sum = _mm256_setzero_pd();
    double accum_sum_aux;

    unsigned long index;
    for (index = 0; index < (cords_len - 4); index += 4) {
        curr = end;                                                 // x0,y0,x1,y1
        forw = _mm256_load_pd((const double *)&cords[index + 2]);   // x2,y2,x3,y3
        end = _mm256_load_pd((const double *)&cords[index + 4]);    // x4,y4,x5,y5

        coef_0 = _mm256_permute2f128_pd(curr, forw, 0b00110001); // x1, y1, x3, y3
        coef_1 = _mm256_permute2f128_pd(forw, end, 0b00100000); // x2, y2, x4, y4

        //_mm256_hsub_pd(a, b) == a0 - a1, b0 - b1, a2 - a3, b2 - b3
        accum_sum = _mm256_add_pd(
            accum_sum,
            _mm256_hsub_pd( // x0*y1 - y0*x1, x1*y2 - y1x2, x2*y3 - y2*x3, x3*y4 - y3*x4
                _mm256_mul_pd( // x0*y1, y0*x1, x2*y3, y2*x3
                    _mm256_permute2f128_pd(curr, forw, 0b00100000),  // x0, y0, x2, y2
                    _mm256_shuffle_pd(coef_0, coef_0, 0b0101)  // y1, x1, y3, x3
                ),
                _mm256_mul_pd(coef_0, _mm256_shuffle_pd(coef_1, coef_1, 0b0101)) // y2, x2, y4, x4
                // ^^^^^^^^^^^^^^^  x1*y2, y1*x2, x3*y4, y3*x4
            )
        );
    }

    accum_sum = _mm256_hadd_pd(accum_sum, _mm256_permute2f128_pd(accum_sum, accum_sum, 1)); // a0+a1, a2+a3, a2+a3, a0+a1
    accum_sum = _mm256_hadd_pd(accum_sum, accum_sum); // a0+a1+a2+a3, ...
    for (accum_sum_aux = _mm_cvtsd_f64(_mm256_castpd256_pd128(accum_sum)); index < (cords_len - 1); index++)
        accum_sum_aux += _calc_diff_of_adj_prods(cords, index);

    return accum_sum_aux;
//    return scalar_half(scalar_abs(accum_sum_aux));
}