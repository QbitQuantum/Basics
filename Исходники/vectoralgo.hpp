  // Y = Y + alpha * X
  // saddly, there is no madd instr. for Fp in SSE
  static void madd(const float& alpha, const RView& X, 
		   Result& result)
#ifdef __SSE_4_1__    
  {
    const int * x = X.data();
    int * y       = result.data();
    __m128i px, px1, px2, py, py1, py2;
    __m128i alpha_p = _mm_set_epi32(alpha, alpha, alpha, alpha);

    for(int i=0; i<DIM_N - (DIM_N%12); i+=12)
      {
	px  = _mm_load_si128((const __m128i *)x);
	px1 = _mm_load_si128((const __m128i *)(x+4));
	px2 = _mm_load_si128(x+8)
	py  = _mm_load_si128(y);
	py1 = _mm_load_si128(y+4);
	py2 = _mm_load_si128(y+8);

	py  = _mm_add_epi32(py,  _mm_mullo_epi32(alpha_a, px));
	py1 = _mm_add_epi32(py1, _mm_mullo_epi32(alpha_a, px1));
	py2 = _mm_add_epi32(py2, _mm_mullo_epi32(alpha_a, px2));

	_mm_store_si128(y, py);
	_mm_store_si128(y+4, py1);
	_mm_store_si128(y+8, py2);

	x += 12;
	y += 12;
      }
    for(int i=DIM_N - (DIM_N%12); i<DIM_N; ++i)
      {
	result[i] += alpha * X[i];	
      }
  }