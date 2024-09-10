void demod_64qam_lte_s_sse(const cf_t *symbols, short *llr, int nsymbols) 
{
  float *symbolsPtr = (float*) symbols;
  __m128i *resultPtr = (__m128i*) llr;
  __m128 symbol1, symbol2; 
  __m128i symbol_i1, symbol_i2, symbol_i, symbol_abs, symbol_abs2;
  __m128i offset1 = _mm_set1_epi16(4*SCALE_SHORT_CONV_QAM64/sqrt(42));
  __m128i offset2 = _mm_set1_epi16(2*SCALE_SHORT_CONV_QAM64/sqrt(42));
  __m128 scale_v = _mm_set1_ps(-SCALE_SHORT_CONV_QAM64);
  __m128i result11, result12, result13, result22, result21,result23, result31, result32, result33; 

  __m128i shuffle_negated_1 = _mm_set_epi8(7,6,5,4,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,3,2,1,0);
  __m128i shuffle_negated_2 = _mm_set_epi8(0xff,0xff,0xff,0xff,11,10,9,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);
  __m128i shuffle_negated_3 = _mm_set_epi8(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,15,14,13,12,0xff,0xff,0xff,0xff);

  __m128i shuffle_abs_1 = _mm_set_epi8(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,3,2,1,0,0xff,0xff,0xff,0xff);
  __m128i shuffle_abs_2 = _mm_set_epi8(11,10,9,8,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,7,6,5,4);
  __m128i shuffle_abs_3 = _mm_set_epi8(0xff,0xff,0xff,0xff,15,14,13,12,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);

  __m128i shuffle_abs2_1 = _mm_set_epi8(0xff,0xff,0xff,0xff,3,2,1,0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);
  __m128i shuffle_abs2_2 = _mm_set_epi8(0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,7,6,5,4,0xff,0xff,0xff,0xff);
  __m128i shuffle_abs2_3 = _mm_set_epi8(15,14,13,12,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,11,10,9,8);

  for (int i=0;i<nsymbols/4;i++) {
    symbol1   = _mm_load_ps(symbolsPtr); symbolsPtr+=4;
    symbol2   = _mm_load_ps(symbolsPtr); symbolsPtr+=4;
    symbol_i1 = _mm_cvtps_epi32(_mm_mul_ps(symbol1, scale_v));
    symbol_i2 = _mm_cvtps_epi32(_mm_mul_ps(symbol2, scale_v));
    symbol_i  = _mm_packs_epi32(symbol_i1, symbol_i2);
    
    symbol_abs  = _mm_abs_epi16(symbol_i);
    symbol_abs  = _mm_sub_epi16(symbol_abs, offset1);
    symbol_abs2 = _mm_sub_epi16(_mm_abs_epi16(symbol_abs), offset2);
    
    result11 = _mm_shuffle_epi8(symbol_i, shuffle_negated_1);  
    result12 = _mm_shuffle_epi8(symbol_abs, shuffle_abs_1);  
    result13 = _mm_shuffle_epi8(symbol_abs2, shuffle_abs2_1);  

    result21 = _mm_shuffle_epi8(symbol_i, shuffle_negated_2);  
    result22 = _mm_shuffle_epi8(symbol_abs, shuffle_abs_2);  
    result23 = _mm_shuffle_epi8(symbol_abs2, shuffle_abs2_2);  

    result31 = _mm_shuffle_epi8(symbol_i, shuffle_negated_3);  
    result32 = _mm_shuffle_epi8(symbol_abs, shuffle_abs_3);  
    result33 = _mm_shuffle_epi8(symbol_abs2, shuffle_abs2_3);  

    _mm_store_si128(resultPtr, _mm_or_si128(_mm_or_si128(result11, result12),result13)); resultPtr++;
    _mm_store_si128(resultPtr, _mm_or_si128(_mm_or_si128(result21, result22),result23)); resultPtr++;
    _mm_store_si128(resultPtr, _mm_or_si128(_mm_or_si128(result31, result32),result33)); resultPtr++;
  }
  for (int i=4*(nsymbols/4);i<nsymbols;i++) {
    float yre = (short) (SCALE_SHORT_CONV_QAM64*crealf(symbols[i]));
    float yim = (short) (SCALE_SHORT_CONV_QAM64*cimagf(symbols[i]));

    llr[6*i+0] = -yre;
    llr[6*i+1] = -yim;
    llr[6*i+2] = abs(yre)-4*SCALE_SHORT_CONV_QAM64/sqrt(42);
    llr[6*i+3] = abs(yim)-4*SCALE_SHORT_CONV_QAM64/sqrt(42);
    llr[6*i+4] = abs(llr[6*i+2])-2*SCALE_SHORT_CONV_QAM64/sqrt(42);
    llr[6*i+5] = abs(llr[6*i+3])-2*SCALE_SHORT_CONV_QAM64/sqrt(42);        
  }
}