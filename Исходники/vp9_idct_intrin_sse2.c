void vp9_iht8x8_64_add_sse2(const tran_low_t *input, uint8_t *dest, int stride,
                            int tx_type) {
  __m128i in[8];
  const __m128i final_rounding = _mm_set1_epi16(1 << 4);

  // load input data
  in[0] = load_input_data8(input);
  in[1] = load_input_data8(input + 8 * 1);
  in[2] = load_input_data8(input + 8 * 2);
  in[3] = load_input_data8(input + 8 * 3);
  in[4] = load_input_data8(input + 8 * 4);
  in[5] = load_input_data8(input + 8 * 5);
  in[6] = load_input_data8(input + 8 * 6);
  in[7] = load_input_data8(input + 8 * 7);

  switch (tx_type) {
    case DCT_DCT:
      vpx_idct8_sse2(in);
      vpx_idct8_sse2(in);
      break;
    case ADST_DCT:
      vpx_idct8_sse2(in);
      iadst8_sse2(in);
      break;
    case DCT_ADST:
      iadst8_sse2(in);
      vpx_idct8_sse2(in);
      break;
    default:
      assert(tx_type == ADST_ADST);
      iadst8_sse2(in);
      iadst8_sse2(in);
      break;
  }

  // Final rounding and shift
  in[0] = _mm_adds_epi16(in[0], final_rounding);
  in[1] = _mm_adds_epi16(in[1], final_rounding);
  in[2] = _mm_adds_epi16(in[2], final_rounding);
  in[3] = _mm_adds_epi16(in[3], final_rounding);
  in[4] = _mm_adds_epi16(in[4], final_rounding);
  in[5] = _mm_adds_epi16(in[5], final_rounding);
  in[6] = _mm_adds_epi16(in[6], final_rounding);
  in[7] = _mm_adds_epi16(in[7], final_rounding);

  in[0] = _mm_srai_epi16(in[0], 5);
  in[1] = _mm_srai_epi16(in[1], 5);
  in[2] = _mm_srai_epi16(in[2], 5);
  in[3] = _mm_srai_epi16(in[3], 5);
  in[4] = _mm_srai_epi16(in[4], 5);
  in[5] = _mm_srai_epi16(in[5], 5);
  in[6] = _mm_srai_epi16(in[6], 5);
  in[7] = _mm_srai_epi16(in[7], 5);

  recon_and_store(dest + 0 * stride, in[0]);
  recon_and_store(dest + 1 * stride, in[1]);
  recon_and_store(dest + 2 * stride, in[2]);
  recon_and_store(dest + 3 * stride, in[3]);
  recon_and_store(dest + 4 * stride, in[4]);
  recon_and_store(dest + 5 * stride, in[5]);
  recon_and_store(dest + 6 * stride, in[6]);
  recon_and_store(dest + 7 * stride, in[7]);
}