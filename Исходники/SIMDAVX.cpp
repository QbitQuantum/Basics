		while( i-- ) {
			sad += Math::abs( *src1++ - *src2++ );
		}

		// Zero upper half of AVX registers to avoid AVX-SSE transition penalties
		_mm256_zeroupper( );

		return sad;
	}

	float SIMDAVX::SSD( const float* src1, const float* src2, const size_t n ) const
	{
		size_t i = n >> 3;

		__m256 a, b, diff, sqr, sum;
		sum = _mm256_setzero_ps( );
		if( ( ( size_t ) src1 | ( size_t ) src2 ) & 0x1f ) {
			while( i-- ) {
				a = _mm256_loadu_ps( src1 );
				b = _mm256_loadu_ps( src2 );
				diff = _mm256_sub_ps( a, b );
				sqr = _mm256_mul_ps( diff, diff );
				sum = _mm256_add_ps( sum, sqr );
				src1 += 8; src2 += 8;
			}
		} else {
			while( i-- ) {
				a = _mm256_load_ps( src1 );
				b = _mm256_load_ps( src2 );
				diff = _mm256_sub_ps( a, b );
				sqr = _mm256_mul_ps( diff, diff );