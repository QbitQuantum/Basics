    IV SSE2( RegFile & r ) const
    {
        __m128i res = _mm_add_epi16( r.src1[0].i, mV128.i);
		r.dst[0].i = _mm_packus_epi16(res,res);
    }