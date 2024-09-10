	EvalSum& operator -= (const EvalSum& rhs) {
#if defined USE_AVX2_EVAL
		mm = _mm256_sub_epi32(mm, rhs.mm);
#elif defined USE_SSE_EVAL
		m[0] = _mm_sub_epi32(m[0], rhs.m[0]);
		m[1] = _mm_sub_epi32(m[1], rhs.m[1]);
#else
		m_p[0][0] -= rhs.m_p[0][0];
		m_p[0][1] -= rhs.m_p[0][1];
		m_p[1][0] -= rhs.m_p[1][0];
		m_p[1][1] -= rhs.m_p[1][1];
		m_p[2][0] -= rhs.m_p[2][0];
		m_p[2][1] -= rhs.m_p[2][1];
#endif
		return *this;
	}