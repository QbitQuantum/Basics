 template <bool align, bool mask> void LbpEstimate(const uint8_t * src, ptrdiff_t stride, uint8_t * dst, __mmask64 tail = -1)
 {
     __m512i threshold = Load<false, mask>(src, tail);
     __m512i lbp = _mm512_setzero_si512();
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<align, mask>(src - 1 - stride, tail)), threshold), (char)0x01));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<false, mask>(src - stride, tail)), threshold), (char)0x02));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<false, mask>(src + 1 - stride, tail)), threshold), (char)0x04));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<false, mask>(src + 1, tail)), threshold), (char)0x08));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<false, mask>(src + 1 + stride, tail)), threshold), (char)0x10));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<false, mask>(src + stride, tail)), threshold), (char)0x20));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<align, mask>(src - 1 + stride, tail)), threshold), (char)0x40));
     lbp = _mm512_or_si512(lbp, _mm512_maskz_set1_epi8(_mm512_cmpge_epu8_mask((Load<align, mask>(src - 1, tail)), threshold), (char)0x80));
     Store<false, mask>(dst, lbp, tail);
 }