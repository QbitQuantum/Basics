 inline
 bool any() const
 {
     __m512d buf0 = _mm512_or_pd(val[ 0], val[ 1]);
     return _mm512_test_epi64_mask(
         _mm512_castpd_si512(buf0),
         _mm512_castpd_si512(buf0));
 }