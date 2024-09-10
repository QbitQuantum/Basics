/**
 * \brief quantize transformed coefficents
 *
 */
void kvz_quant_flat_avx2(const encoder_state_t * const state, coeff_t *coef, coeff_t *q_coef, int32_t width,
  int32_t height, int8_t type, int8_t scan_idx, int8_t block_type)
{
  const encoder_control_t * const encoder = state->encoder_control;
  const uint32_t log2_block_size = kvz_g_convert_to_bit[width] + 2;
  const uint32_t * const scan = kvz_g_sig_last_scan[scan_idx][log2_block_size - 1];

  int32_t qp_scaled = kvz_get_scaled_qp(type, state->global->QP, (encoder->bitdepth - 8) * 6);
  const uint32_t log2_tr_size = kvz_g_convert_to_bit[width] + 2;
  const int32_t scalinglist_type = (block_type == CU_INTRA ? 0 : 3) + (int8_t)("\0\3\1\2"[type]);
  const int32_t *quant_coeff = encoder->scaling_list.quant_coeff[log2_tr_size - 2][scalinglist_type][qp_scaled % 6];
  const int32_t transform_shift = MAX_TR_DYNAMIC_RANGE - encoder->bitdepth - log2_tr_size; //!< Represents scaling through forward transform
  const int32_t q_bits = QUANT_SHIFT + qp_scaled / 6 + transform_shift;
  const int32_t add = ((state->global->slicetype == KVZ_SLICE_I) ? 171 : 85) << (q_bits - 9);
  const int32_t q_bits8 = q_bits - 8;

  assert(quant_coeff[0] <= (1 << 15) - 1 && quant_coeff[0] >= -(1 << 15)); //Assuming flat values to fit int16_t

  uint32_t ac_sum = 0;

  __m256i v_ac_sum = _mm256_setzero_si256();
  __m256i v_quant_coeff = _mm256_set1_epi16(quant_coeff[0]);

  for (int32_t n = 0; n < width * height; n += 16) {

    __m256i v_level = _mm256_loadu_si256((__m256i*)&(coef[n]));
    __m256i v_sign = _mm256_cmpgt_epi16(_mm256_setzero_si256(), v_level);
    v_sign = _mm256_or_si256(v_sign, _mm256_set1_epi16(1));

    v_level = _mm256_abs_epi16(v_level);
    __m256i low_a = _mm256_unpacklo_epi16(v_level, _mm256_set1_epi16(0));
    __m256i high_a = _mm256_unpackhi_epi16(v_level, _mm256_set1_epi16(0));

    __m256i low_b = _mm256_unpacklo_epi16(v_quant_coeff, _mm256_set1_epi16(0));
    __m256i high_b = _mm256_unpackhi_epi16(v_quant_coeff, _mm256_set1_epi16(0));

    __m256i v_level32_a = _mm256_madd_epi16(low_a, low_b);
    __m256i v_level32_b = _mm256_madd_epi16(high_a, high_b);

    v_level32_a = _mm256_add_epi32(v_level32_a, _mm256_set1_epi32(add));
    v_level32_b = _mm256_add_epi32(v_level32_b, _mm256_set1_epi32(add));

    v_level32_a = _mm256_srai_epi32(v_level32_a, q_bits);
    v_level32_b = _mm256_srai_epi32(v_level32_b, q_bits);

    v_level = _mm256_packs_epi32(v_level32_a, v_level32_b);
    v_level = _mm256_sign_epi16(v_level, v_sign);

    _mm256_storeu_si256((__m256i*)&(q_coef[n]), v_level);

    v_ac_sum = _mm256_add_epi32(v_ac_sum, v_level32_a);
    v_ac_sum = _mm256_add_epi32(v_ac_sum, v_level32_b);
  }

  __m128i temp = _mm_add_epi32(_mm256_castsi256_si128(v_ac_sum), _mm256_extracti128_si256(v_ac_sum, 1));
  temp = _mm_add_epi32(temp, _mm_shuffle_epi32(temp, KVZ_PERMUTE(2, 3, 0, 1)));
  temp = _mm_add_epi32(temp, _mm_shuffle_epi32(temp, KVZ_PERMUTE(1, 0, 1, 0)));
  ac_sum += _mm_cvtsi128_si32(temp);

  if (!(encoder->sign_hiding && ac_sum >= 2)) return;

  int32_t delta_u[LCU_WIDTH*LCU_WIDTH >> 2];

  for (int32_t n = 0; n < width * height; n += 16) {

    __m256i v_level = _mm256_loadu_si256((__m256i*)&(coef[n]));

    v_level = _mm256_abs_epi16(v_level);
    __m256i low_a = _mm256_unpacklo_epi16(v_level, _mm256_set1_epi16(0));
    __m256i high_a = _mm256_unpackhi_epi16(v_level, _mm256_set1_epi16(0));

    __m256i low_b = _mm256_unpacklo_epi16(v_quant_coeff, _mm256_set1_epi16(0));
    __m256i high_b = _mm256_unpackhi_epi16(v_quant_coeff, _mm256_set1_epi16(0));

    __m256i v_level32_a = _mm256_madd_epi16(low_a, low_b);
    __m256i v_level32_b = _mm256_madd_epi16(high_a, high_b);

    v_level32_a = _mm256_add_epi32(v_level32_a, _mm256_set1_epi32(add));
    v_level32_b = _mm256_add_epi32(v_level32_b, _mm256_set1_epi32(add));

    v_level32_a = _mm256_srai_epi32(v_level32_a, q_bits);
    v_level32_b = _mm256_srai_epi32(v_level32_b, q_bits);

    v_level = _mm256_packs_epi32(v_level32_a, v_level32_b);

    __m256i v_coef = _mm256_loadu_si256((__m256i*)&(coef[n]));
    __m256i v_coef_a = _mm256_unpacklo_epi16(_mm256_abs_epi16(v_coef), _mm256_set1_epi16(0));
    __m256i v_coef_b = _mm256_unpackhi_epi16(_mm256_abs_epi16(v_coef), _mm256_set1_epi16(0));
    __m256i v_quant_coeff_a = _mm256_unpacklo_epi16(v_quant_coeff, _mm256_set1_epi16(0));
    __m256i v_quant_coeff_b = _mm256_unpackhi_epi16(v_quant_coeff, _mm256_set1_epi16(0));
    v_coef_a = _mm256_madd_epi16(v_coef_a, v_quant_coeff_a);
    v_coef_b = _mm256_madd_epi16(v_coef_b, v_quant_coeff_b);
    v_coef_a = _mm256_sub_epi32(v_coef_a, _mm256_slli_epi32(_mm256_unpacklo_epi16(v_level, _mm256_set1_epi16(0)), q_bits) );
    v_coef_b = _mm256_sub_epi32(v_coef_b, _mm256_slli_epi32(_mm256_unpackhi_epi16(v_level, _mm256_set1_epi16(0)), q_bits) );
    v_coef_a = _mm256_srai_epi32(v_coef_a, q_bits8);
    v_coef_b = _mm256_srai_epi32(v_coef_b, q_bits8);
    
    _mm_storeu_si128((__m128i*)&(delta_u[n+0*4]), _mm256_castsi256_si128(v_coef_a));
    _mm_storeu_si128((__m128i*)&(delta_u[n+2*4]), _mm256_extracti128_si256(v_coef_a, 1));
    _mm_storeu_si128((__m128i*)&(delta_u[n+1*4]), _mm256_castsi256_si128(v_coef_b));
    _mm_storeu_si128((__m128i*)&(delta_u[n+3*4]), _mm256_extracti128_si256(v_coef_b, 1));
  }

  if (ac_sum >= 2) {
#define SCAN_SET_SIZE 16
#define LOG2_SCAN_SET_SIZE 4
    int32_t n, last_cg = -1, abssum = 0, subset, subpos;
    for (subset = (width*height - 1) >> LOG2_SCAN_SET_SIZE; subset >= 0; subset--) {
      int32_t first_nz_pos_in_cg = SCAN_SET_SIZE, last_nz_pos_in_cg = -1;
      subpos = subset << LOG2_SCAN_SET_SIZE;
      abssum = 0;

      // Find last coeff pos
      for (n = SCAN_SET_SIZE - 1; n >= 0; n--)  {
        if (q_coef[scan[n + subpos]])  {
          last_nz_pos_in_cg = n;
          break;
        }
      }

      // First coeff pos
      for (n = 0; n <SCAN_SET_SIZE; n++) {
        if (q_coef[scan[n + subpos]]) {
          first_nz_pos_in_cg = n;
          break;
        }
      }

      // Sum all kvz_quant coeffs between first and last
      for (n = first_nz_pos_in_cg; n <= last_nz_pos_in_cg; n++) {
        abssum += q_coef[scan[n + subpos]];
      }

      if (last_nz_pos_in_cg >= 0 && last_cg == -1) {
        last_cg = 1;
      }

      if (last_nz_pos_in_cg - first_nz_pos_in_cg >= 4) {
        int32_t signbit = (q_coef[scan[subpos + first_nz_pos_in_cg]] > 0 ? 0 : 1);
        if (signbit != (abssum & 0x1)) { // compare signbit with sum_parity
          int32_t min_cost_inc = 0x7fffffff, min_pos = -1, cur_cost = 0x7fffffff;
          int16_t final_change = 0, cur_change = 0;
          for (n = (last_cg == 1 ? last_nz_pos_in_cg : SCAN_SET_SIZE - 1); n >= 0; n--) {
            uint32_t blkPos = scan[n + subpos];
            if (q_coef[blkPos] != 0) {
              if (delta_u[blkPos] > 0) {
                cur_cost = -delta_u[blkPos];
                cur_change = 1;
              }
              else if (n == first_nz_pos_in_cg && abs(q_coef[blkPos]) == 1) {
                cur_cost = 0x7fffffff;
              }
              else {
                cur_cost = delta_u[blkPos];
                cur_change = -1;
              }
            }
            else if (n < first_nz_pos_in_cg && ((coef[blkPos] >= 0) ? 0 : 1) != signbit) {
              cur_cost = 0x7fffffff;
            }
            else {
              cur_cost = -delta_u[blkPos];
              cur_change = 1;
            }

            if (cur_cost < min_cost_inc) {
              min_cost_inc = cur_cost;
              final_change = cur_change;
              min_pos = blkPos;
            }
          } // CG loop

          if (q_coef[min_pos] == 32767 || q_coef[min_pos] == -32768) {
            final_change = -1;
          }

          if (coef[min_pos] >= 0) q_coef[min_pos] += final_change;
          else q_coef[min_pos] -= final_change;
        } // Hide
      }
      if (last_cg == 1) last_cg = 0;
    }

#undef SCAN_SET_SIZE
#undef LOG2_SCAN_SET_SIZE
  }