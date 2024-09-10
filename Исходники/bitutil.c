unsigned bitdelta32(unsigned *in, unsigned n, unsigned *out, unsigned start, unsigned inc) {
    #ifdef __SSE2__
  unsigned *ip,b,*op = out; 
  __m128i bv = _mm_setzero_si128(), sv = _mm_set1_epi32(start), cv = _mm_set1_epi32(inc), dv;
  for(ip = in; ip != in+(n&~(4-1)); ip += 4) { 
    __m128i iv = _mm_loadu_si128((__m128i *)ip); 
	bv = _mm_or_si128(bv, dv = _mm_sub_epi32(DELTA128_32(iv,sv),cv)); 
	sv = iv; 
	_mm_storeu_si128((__m128i *)op, dv); 
	op += 4; 
  }
  start = (unsigned)_mm_cvtsi128_si32(_mm_srli_si128(sv,12));
  HOR128_32(bv, b);
  while(ip < in+n) { unsigned x = *ip-start-inc; start = *ip++; b |= x; *op++ = x; }
    #else
  typeof(in[0]) b = 0,*op = out; BITDELTA(in, n, inc, start, b |= _x;*op++ = _x);
    #endif
  return bsr32(b);
}