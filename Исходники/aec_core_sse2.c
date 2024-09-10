static __m128 mm_pow_ps(__m128 a, __m128 b) {
  // a^b = exp2(b * log2(a))
  //   exp2(x) and log2(x) are calculated using polynomial approximations.
  __m128 log2_a, b_log2_a, a_exp_b;

  // Calculate log2(x), x = a.
  {
    // To calculate log2(x), we decompose x like this:
    //   x = y * 2^n
    //     n is an integer
    //     y is in the [1.0, 2.0) range
    //
    //   log2(x) = log2(y) + n
    //     n       can be evaluated by playing with float representation.
    //     log2(y) in a small range can be approximated, this code uses an order
    //             five polynomial approximation. The coefficients have been
    //             estimated with the Remez algorithm and the resulting
    //             polynomial has a maximum relative error of 0.00086%.

    // Compute n.
    //    This is done by masking the exponent, shifting it into the top bit of
    //    the mantissa, putting eight into the biased exponent (to shift/
    //    compensate the fact that the exponent has been shifted in the top/
    //    fractional part and finally getting rid of the implicit leading one
    //    from the mantissa by substracting it out.
    static const ALIGN16_BEG int float_exponent_mask[4] ALIGN16_END = {
        0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000};
    static const ALIGN16_BEG int eight_biased_exponent[4] ALIGN16_END = {
        0x43800000, 0x43800000, 0x43800000, 0x43800000};
    static const ALIGN16_BEG int implicit_leading_one[4] ALIGN16_END = {
        0x43BF8000, 0x43BF8000, 0x43BF8000, 0x43BF8000};
    static const int shift_exponent_into_top_mantissa = 8;
    const __m128 two_n = _mm_and_ps(a, *((__m128*)float_exponent_mask));
    const __m128 n_1 = _mm_castsi128_ps(_mm_srli_epi32(
        _mm_castps_si128(two_n), shift_exponent_into_top_mantissa));
    const __m128 n_0 = _mm_or_ps(n_1, *((__m128*)eight_biased_exponent));
    const __m128 n = _mm_sub_ps(n_0, *((__m128*)implicit_leading_one));

    // Compute y.
    static const ALIGN16_BEG int mantissa_mask[4] ALIGN16_END = {
        0x007FFFFF, 0x007FFFFF, 0x007FFFFF, 0x007FFFFF};
    static const ALIGN16_BEG int zero_biased_exponent_is_one[4] ALIGN16_END = {
        0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000};
    const __m128 mantissa = _mm_and_ps(a, *((__m128*)mantissa_mask));
    const __m128 y =
        _mm_or_ps(mantissa, *((__m128*)zero_biased_exponent_is_one));

    // Approximate log2(y) ~= (y - 1) * pol5(y).
    //    pol5(y) = C5 * y^5 + C4 * y^4 + C3 * y^3 + C2 * y^2 + C1 * y + C0
    static const ALIGN16_BEG float ALIGN16_END C5[4] = {
        -3.4436006e-2f, -3.4436006e-2f, -3.4436006e-2f, -3.4436006e-2f};
    static const ALIGN16_BEG float ALIGN16_END
        C4[4] = {3.1821337e-1f, 3.1821337e-1f, 3.1821337e-1f, 3.1821337e-1f};
    static const ALIGN16_BEG float ALIGN16_END
        C3[4] = {-1.2315303f, -1.2315303f, -1.2315303f, -1.2315303f};
    static const ALIGN16_BEG float ALIGN16_END
        C2[4] = {2.5988452f, 2.5988452f, 2.5988452f, 2.5988452f};
    static const ALIGN16_BEG float ALIGN16_END
        C1[4] = {-3.3241990f, -3.3241990f, -3.3241990f, -3.3241990f};
    static const ALIGN16_BEG float ALIGN16_END
        C0[4] = {3.1157899f, 3.1157899f, 3.1157899f, 3.1157899f};
    const __m128 pol5_y_0 = _mm_mul_ps(y, *((__m128*)C5));
    const __m128 pol5_y_1 = _mm_add_ps(pol5_y_0, *((__m128*)C4));
    const __m128 pol5_y_2 = _mm_mul_ps(pol5_y_1, y);
    const __m128 pol5_y_3 = _mm_add_ps(pol5_y_2, *((__m128*)C3));
    const __m128 pol5_y_4 = _mm_mul_ps(pol5_y_3, y);
    const __m128 pol5_y_5 = _mm_add_ps(pol5_y_4, *((__m128*)C2));
    const __m128 pol5_y_6 = _mm_mul_ps(pol5_y_5, y);
    const __m128 pol5_y_7 = _mm_add_ps(pol5_y_6, *((__m128*)C1));
    const __m128 pol5_y_8 = _mm_mul_ps(pol5_y_7, y);
    const __m128 pol5_y = _mm_add_ps(pol5_y_8, *((__m128*)C0));
    const __m128 y_minus_one =
        _mm_sub_ps(y, *((__m128*)zero_biased_exponent_is_one));
    const __m128 log2_y = _mm_mul_ps(y_minus_one, pol5_y);

    // Combine parts.
    log2_a = _mm_add_ps(n, log2_y);
  }

  // b * log2(a)
  b_log2_a = _mm_mul_ps(b, log2_a);

  // Calculate exp2(x), x = b * log2(a).
  {
    // To calculate 2^x, we decompose x like this:
    //   x = n + y
    //     n is an integer, the value of x - 0.5 rounded down, therefore
    //     y is in the [0.5, 1.5) range
    //
    //   2^x = 2^n * 2^y
    //     2^n can be evaluated by playing with float representation.
    //     2^y in a small range can be approximated, this code uses an order two
    //         polynomial approximation. The coefficients have been estimated
    //         with the Remez algorithm and the resulting polynomial has a
    //         maximum relative error of 0.17%.

    // To avoid over/underflow, we reduce the range of input to ]-127, 129].
    static const ALIGN16_BEG float max_input[4] ALIGN16_END = {129.f, 129.f,
                                                               129.f, 129.f};
    static const ALIGN16_BEG float min_input[4] ALIGN16_END = {
        -126.99999f, -126.99999f, -126.99999f, -126.99999f};
    const __m128 x_min = _mm_min_ps(b_log2_a, *((__m128*)max_input));
    const __m128 x_max = _mm_max_ps(x_min, *((__m128*)min_input));
    // Compute n.
    static const ALIGN16_BEG float half[4] ALIGN16_END = {0.5f, 0.5f,
                                                          0.5f, 0.5f};
    const __m128 x_minus_half = _mm_sub_ps(x_max, *((__m128*)half));
    const __m128i x_minus_half_floor = _mm_cvtps_epi32(x_minus_half);
    // Compute 2^n.
    static const ALIGN16_BEG int float_exponent_bias[4] ALIGN16_END = {
        127, 127, 127, 127};
    static const int float_exponent_shift = 23;
    const __m128i two_n_exponent =
        _mm_add_epi32(x_minus_half_floor, *((__m128i*)float_exponent_bias));
    const __m128 two_n =
        _mm_castsi128_ps(_mm_slli_epi32(two_n_exponent, float_exponent_shift));
    // Compute y.
    const __m128 y = _mm_sub_ps(x_max, _mm_cvtepi32_ps(x_minus_half_floor));
    // Approximate 2^y ~= C2 * y^2 + C1 * y + C0.
    static const ALIGN16_BEG float C2[4] ALIGN16_END = {
        3.3718944e-1f, 3.3718944e-1f, 3.3718944e-1f, 3.3718944e-1f};
    static const ALIGN16_BEG float C1[4] ALIGN16_END = {
        6.5763628e-1f, 6.5763628e-1f, 6.5763628e-1f, 6.5763628e-1f};
    static const ALIGN16_BEG float C0[4] ALIGN16_END = {1.0017247f, 1.0017247f,
                                                        1.0017247f, 1.0017247f};
    const __m128 exp2_y_0 = _mm_mul_ps(y, *((__m128*)C2));
    const __m128 exp2_y_1 = _mm_add_ps(exp2_y_0, *((__m128*)C1));
    const __m128 exp2_y_2 = _mm_mul_ps(exp2_y_1, y);
    const __m128 exp2_y = _mm_add_ps(exp2_y_2, *((__m128*)C0));

    // Combine parts.
    a_exp_b = _mm_mul_ps(exp2_y, two_n);
  }
  return a_exp_b;
}