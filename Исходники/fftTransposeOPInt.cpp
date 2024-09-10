/* 
 * Intel single precision, _mm_stream_pd version, used for transposing
 * from a stripe buffer to columns. 
 */
static void fftOPSubTrans(
  const FFTComplex	*_src,
  FFTComplex		*_dst,
  size_t			srcRowSize,		// src, in FFTComplex, a.k.a. src numCols
  size_t			dstRowSize)		// dst, in FFTComplex, a.k.a. dst numCols
{
	double *src = (double *)_src;
	double *dst = (double *)_dst;
	
	dumpSub("fftOPSubTrans start", _src, srcRowSize);
	
	/* 
	 * row and col refer to coordinates in src 
	 * row size of dst is dstRowSize
	 */
	unsigned curcol;
	
	for(curcol=0; curcol<FFT_COMPLEX_PER_SUBMATRIX; curcol+=2) {
		__m128d vin1;
		__m128d vin2;
		__m128d vin3;
		__m128d vin4;
		__m128d vin5;
		__m128d vin6;
		__m128d vin7;
		__m128d vin8;
		
		__m128d vOut_row1_1;
		__m128d vOut_row1_2;
		__m128d vOut_row1_3;
		__m128d vOut_row1_4;
		__m128d vOut_row2_1;
		__m128d vOut_row2_2;
		__m128d vOut_row2_3;
		__m128d vOut_row2_4;
		
		const double *pIn = src + curcol;
		double *pOut = dst + curcol*dstRowSize;
		
		// load in two columns from src at curcol
		vin1 = _mm_load_pd(pIn+0*srcRowSize);
		vin2 = _mm_load_pd(pIn+1*srcRowSize);
		vin3 = _mm_load_pd(pIn+2*srcRowSize);
		vin4 = _mm_load_pd(pIn+3*srcRowSize);
		vin5 = _mm_load_pd(pIn+4*srcRowSize);
		vin6 = _mm_load_pd(pIn+5*srcRowSize);
		vin7 = _mm_load_pd(pIn+6*srcRowSize);
		vin8 = _mm_load_pd(pIn+7*srcRowSize);
		
		///////////////////////////////////////////////
		// transpose for first row out
		
		vOut_row1_1 = _mm_unpacklo_pd(vin1, vin2);
		vOut_row1_2 = _mm_unpacklo_pd(vin3, vin4);
		vOut_row1_3 = _mm_unpacklo_pd(vin5, vin6);
		vOut_row1_4 = _mm_unpacklo_pd(vin7, vin8);
		
		_mm_stream_pd(pOut+(0*FFT_COMPLEX_PER_VECTOR), vOut_row1_1);
		_mm_stream_pd(pOut+(1*FFT_COMPLEX_PER_VECTOR), vOut_row1_2);
		_mm_stream_pd(pOut+(2*FFT_COMPLEX_PER_VECTOR), vOut_row1_3);
		_mm_stream_pd(pOut+(3*FFT_COMPLEX_PER_VECTOR), vOut_row1_4);
		
		///////////////////////////////////////////////
		// transpose for second row out
		pOut += dstRowSize;
		
		vOut_row2_1 = _mm_unpackhi_pd(vin1, vin2);
		vOut_row2_2 = _mm_unpackhi_pd(vin3, vin4);
		vOut_row2_3 = _mm_unpackhi_pd(vin5, vin6);
		vOut_row2_4 = _mm_unpackhi_pd(vin7, vin8);
		
		_mm_stream_pd(pOut+(0*FFT_COMPLEX_PER_VECTOR), vOut_row2_1);
		_mm_stream_pd(pOut+(1*FFT_COMPLEX_PER_VECTOR), vOut_row2_2);
		_mm_stream_pd(pOut+(2*FFT_COMPLEX_PER_VECTOR), vOut_row2_3);
		_mm_stream_pd(pOut+(3*FFT_COMPLEX_PER_VECTOR), vOut_row2_4);
	}
	
	dumpSub("fftOPSubTrans end", _dst, dstRowSize);
}