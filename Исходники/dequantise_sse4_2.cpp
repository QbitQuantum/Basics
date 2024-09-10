template<> void dequantise_sse4_2<4,8,2, int32_t>(QuantisationMatrix *qmatrix,
                                  int32_t *idata,
                                  void *_odata,
                                  int ostride,
                                  int, int, int) {
  int32_t *odata = (int32_t *)_odata;
  const int slice_width  = 4;
  const int slice_height = 8;
  const int Y = 0;
  const int X = 0;
  const int N = 0;

  int32_t * const optr = &odata[Y*slice_height*ostride + X*slice_width];
  const int32_t * iptr = &idata[N*slice_height*slice_width];

  __m128i D0;
  {
    D0 = _mm_load_si128((__m128i *)&iptr[ 0]); // [  0  1  2  3 ] (Q)
    __m128i QF = _mm_unpacklo_epi64(_mm_load_si128((__m128i *)&qmatrix->qfactor[0][0]),
                                    _mm_load_si128((__m128i *)&qmatrix->qfactor[1][1]));
    __m128i QO = _mm_unpacklo_epi64(_mm_load_si128((__m128i *)&qmatrix->qoffset[0][0]),
                                    _mm_load_si128((__m128i *)&qmatrix->qoffset[1][1]));

    __m128i X  = _mm_abs_epi32(D0);
    X = _mm_mullo_epi32(X, QF);
    X = _mm_add_epi32(X, QO);
    X = _mm_srai_epi32(X, 2);
    D0 = _mm_sign_epi32(X, D0);
  }
  __m128i D4;
  {
    D4 = _mm_load_si128((__m128i *)&iptr[ 4]); // [  4  5  6  7 ] (Q)
    __m128i QF = _mm_unpacklo_epi64(_mm_load_si128((__m128i *)&qmatrix->qfactor[1][2]),
                                    _mm_load_si128((__m128i *)&qmatrix->qfactor[1][3]));
    __m128i QO = _mm_unpacklo_epi64(_mm_load_si128((__m128i *)&qmatrix->qoffset[1][2]),
                                    _mm_load_si128((__m128i *)&qmatrix->qoffset[1][3]));
    __m128i X  = _mm_abs_epi32(D4);
    X = _mm_mullo_epi32(X, QF);
    X = _mm_add_epi32(X, QO);
    X = _mm_srai_epi32(X, 2);
    D4 = _mm_sign_epi32(X, D4);
  }

  const __m128i D8  = LOAD_QUANTISED(&iptr[ 8], qmatrix, 2, 1); // [  8  9 10 11 ]
  const __m128i D12 = LOAD_QUANTISED(&iptr[12], qmatrix, 2, 1); // [ 12 13 14 15 ]
  const __m128i D16 = LOAD_QUANTISED(&iptr[16], qmatrix, 2, 2); // [ 16 17 18 19 ]
  const __m128i D20 = LOAD_QUANTISED(&iptr[20], qmatrix, 2, 2); // [ 20 21 22 23 ]
  const __m128i D24 = LOAD_QUANTISED(&iptr[24], qmatrix, 2, 3); // [ 24 25 26 27 ]
  const __m128i D28 = LOAD_QUANTISED(&iptr[28], qmatrix, 2, 3); // [ 28 29 30 31 ]

  const __m128i X0  = _mm_unpacklo_epi32(D0,  D4); // [  0  4  1  5 ]
  const __m128i X1  = _mm_unpackhi_epi32(D0,  D4); // [  2  6  3  7 ]
  const __m128i Y0  = _mm_unpacklo_epi32(X0,  X1); // [  0  2  4  6 ]
  const __m128i Y1  = _mm_unpackhi_epi32(X0,  X1); // [  1  3  5  7 ]

  const __m128i Z0  = _mm_unpacklo_epi32(Y0,  D8); // [  0  8  2  9 ]
  _mm_store_si128((__m128i *)&optr[0*ostride + 0], Z0);
  const __m128i Z1  = _mm_unpackhi_epi32(Y0,  D8); // [  4 10  6 11 ]
  _mm_store_si128((__m128i *)&optr[2*ostride + 0], Z1);

  const __m128i Z2  = _mm_unpacklo_epi32(Y1, D12); // [  1 12  3 13 ]
  _mm_store_si128((__m128i *)&optr[4*ostride + 0], Z2);
  const __m128i Z3  = _mm_unpackhi_epi32(Y1, D12); // [  5 14  7 15 ]
  _mm_store_si128((__m128i *)&optr[6*ostride + 0], Z3);

  const __m128i W0  = _mm_unpacklo_epi32(D16, D24);// [ 16 24 17 25 ]
  _mm_store_si128((__m128i *)&optr[1*ostride + 0], W0);
  const __m128i W1  = _mm_unpackhi_epi32(D16, D24);// [ 18 26 19 27 ]
  _mm_store_si128((__m128i *)&optr[3*ostride + 0], W1);

  const __m128i W2  = _mm_unpacklo_epi32(D20, D28);// [ 20 28 21 29 ]
  _mm_store_si128((__m128i *)&optr[5*ostride + 0], W2);
  const __m128i W3  = _mm_unpackhi_epi32(D20, D28);// [ 22 30 23 31 ]
  _mm_store_si128((__m128i *)&optr[7*ostride + 0], W3);

}