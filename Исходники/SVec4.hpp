	// Operators
	INLINE bool SVec4::operator==(const SVec4 &rhs) const
	{
#ifdef USE_SSE
		SIMDvec dif = _mm_sub_ps( m_128, rhs.m_128 );
		SIMDvec ep = _mm_set1_ps( math::Epsilon );
		SIMDvec neg_ep = _mm_set1_ps( -math::Epsilon );

		return ( 0xf == _mm_movemask_ps( _mm_and_ps( _mm_cmpgt_ps( ep, dif ), _mm_cmplt_ps( neg_ep, dif ) ) ) );
#else
        return math::IsEqual(m_x, rhs.X()) &&
               math::IsEqual(m_y, rhs.Y()) &&
               math::IsEqual(m_z, rhs.Z()) &&
               math::IsEqual(m_w, rhs.W());
#endif
	}