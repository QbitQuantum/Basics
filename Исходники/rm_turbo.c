int srslte_rm_turbo_rx_lut_sse_8bit(int8_t *input, int8_t *output, uint16_t *deinter, uint32_t in_len, uint32_t cb_idx, uint32_t rv_idx)
{
  if (rv_idx < 4 && cb_idx < SRSLTE_NOF_TC_CB_SIZES) {
    uint32_t out_len = 3*srslte_cbsegm_cbsize(cb_idx)+12;

    const __m128i* xPtr   = (const __m128i*) input;
    const __m128i* lutPtr = (const __m128i*) deinter;
    __m128i xVal, lutVal1, lutVal2;

    /* Simplify load if we do not need to wrap (ie high rates) */
    if (in_len <= out_len) {
      for (int i=0;i<in_len/16;i++) {
        xVal   = _mm_loadu_si128(xPtr);
        xPtr ++;
        lutVal1 = _mm_loadu_si128(lutPtr);
        lutPtr++;
        lutVal2 = _mm_loadu_si128(lutPtr);
        lutPtr ++;

        for (int j=0;j<8;j++) {
          int8_t x  = (int8_t)  _mm_extract_epi8(xVal,   j);
          uint16_t l = (uint16_t) _mm_extract_epi16(lutVal1, j);
          output[l] += x;
        }
        for (int j=0;j<8;j++) {
          int8_t x  = (int8_t)  _mm_extract_epi8(xVal,   j+8);
          uint16_t l = (uint16_t) _mm_extract_epi16(lutVal2, j);
          output[l] += x;
        }
      }
      for (int i=16*(in_len/16);i<in_len;i++) {
        output[deinter[i%out_len]] += input[i];
      }
    } else {
      int intCnt = 16;
      int inputCnt = 0;
      int nwrapps = 0;
      while(inputCnt < in_len - 16) {
        xVal   = _mm_loadu_si128(xPtr);
        xPtr ++;
        lutVal1 = _mm_loadu_si128(lutPtr);
        lutPtr++;
        lutVal2 = _mm_loadu_si128(lutPtr);
        lutPtr ++;

        for (int j=0;j<8;j++) {
          int8_t x  = (int8_t)  _mm_extract_epi8(xVal,   j);
          uint16_t l = (uint16_t) _mm_extract_epi16(lutVal1, j);
          output[l] += x;
        }
        for (int j=0;j<8;j++) {
          int8_t x  = (int8_t)  _mm_extract_epi8(xVal,   j+8);
          uint16_t l = (uint16_t) _mm_extract_epi16(lutVal2, j);
          output[l] += x;
        }
        intCnt   += 16;
        inputCnt += 16;
        if (intCnt >= out_len && inputCnt < in_len - 16) {
          /* Copy last elements */
          if ((out_len%16) == 12) {
            for (int j=(nwrapps+1)*out_len-12;j<(nwrapps+1)*out_len;j++) {
              output[deinter[j%out_len]] += input[j];
              inputCnt++;
            }
          } else {
            for (int j=(nwrapps+1)*out_len-4;j<(nwrapps+1)*out_len;j++) {
              output[deinter[j%out_len]] += input[j];
              inputCnt++;
            }
          }
          /* And wrap pointers */
          nwrapps++;
          intCnt = 16;
          xPtr   = (const __m128i*) &input[nwrapps*out_len];
          lutPtr = (const __m128i*) deinter;
        }
      }
      for (int i=inputCnt;i<in_len;i++) {
        output[deinter[i%out_len]] += input[i];
      }
    }


    return 0;
  } else {
    printf("Invalid inputs rv_idx=%d, cb_idx=%d\n", rv_idx, cb_idx);
    return SRSLTE_ERROR_INVALID_INPUTS;
  }
}