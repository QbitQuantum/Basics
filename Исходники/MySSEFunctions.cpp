	void Shuffle16Elems(__m128 &io_data0, __m128 &io_data1, __m128 &io_data2,
		__m128 &io_data3)
	{
		__m128 ccdd1 = _mm_unpackhi_ps(io_data0, io_data1);
		__m128 ccdd2 = _mm_unpackhi_ps(io_data2, io_data3);
		__m128 aabb1 = _mm_unpacklo_ps(io_data0, io_data1);
		__m128 aabb2 = _mm_unpacklo_ps(io_data2, io_data3);

		io_data0 = 
			_mm_castpd_ps(_mm_unpacklo_pd(_mm_castps_pd(aabb1), _mm_castps_pd(aabb2)));
		io_data1 =
			_mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(aabb1), _mm_castps_pd(aabb2)));
		io_data2 =
			_mm_castpd_ps(_mm_unpacklo_pd(_mm_castps_pd(ccdd1), _mm_castps_pd(ccdd2)));
		io_data3 = 
			_mm_castpd_ps(_mm_unpackhi_pd(_mm_castps_pd(ccdd1), _mm_castps_pd(ccdd2)));
	}