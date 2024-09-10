bool SseBitcoinSha256::FindNonce(uint32_t& nonce) {

#if UCFG_BITCOIN_ASM
	CSseData& sseData = SseData();
	return CalcSha256Sse(sseData.m_4w, sseData.m_4midstate, m_midstate_after_3, UCFG_BITCOIN_NPAR, nonce);

#else
	__m128i *m_4w1 = &m_4w[16*UCFG_BITCOIN_WAY];	//!!!?

	__m128i offset = _mm_set_epi32(3, 2, 1, 0);
	for (int i=0; i<UCFG_BITCOIN_NPAR; i+=UCFG_BITCOIN_WAY, nonce+=UCFG_BITCOIN_WAY) {
		m_4w[3] = _mm_set1_epi32(nonce)+offset;
		for (int j=0; j<8; ++j)
			m_4w1[j] = _mm_set1_epi32(m_midstate_after_3[j]);
#if UCFG_BITCOIN_ASM
		CalcSha256Sse(m_4w, m_4midstate, m_4w1, 18, 3, 64);
#else
		CalcRounds(m_4w, m_4midstate, m_4w1, 18, 3, 64);
#endif

#if UCFG_BITCOIN_WAY==6 || UCFG_BITCOIN_WAY==8
		__m128i v[16];
		for (int j=0; j<8; ++j)
			v[j*2] = v[j*2+1] = _mm_set1_epi32(g_sha256_hinit[j]);
#else
		__m128i v[8];
		for (int j=0; j<8; ++j)
			v[j] = _mm_set1_epi32(g_sha256_hinit[j]);
#endif
#if UCFG_BITCOIN_ASM
		__m128i e = CalcSha256Sse(m_4w1, v, v, 16, 0, 61);
#else
		__m128i e = CalcRounds(m_4w1, v, v, 16, 0, 61);				// We enough this
#endif
		__m128i p = _mm_cmpeq_epi32(e + _mm_set1_epi32(g_sha256_hinit[7]), _mm_setzero_si128());
		uint64_t *p64 = (uint64_t*)&p;
		if (p64[0] | p64[1]) {
			if (_mm_extract_epi16(p, 0) != 0)
				return true;
			if (_mm_extract_epi16(p, 2) != 0) {
				nonce += 1;
				return true;
			}
			if (_mm_extract_epi16(p, 4) != 0) {
				nonce += 2;
				return true;
			}
			if (_mm_extract_epi16(p, 6) != 0) {
				nonce += 3;
				return true;
			}
		}

	}
	return false;
#endif
}