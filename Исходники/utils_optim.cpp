int _normoptimized64(const unsigned char*a, const unsigned char*b){
#ifdef USE_PENTIUM4
	return _normoptimized(a,b,64);
#else	
	unsigned long int _dis0a, _dis0b, _dis1a, _dis1b, _dis2a, _dis2b, _dis3a, _dis3b;
	long int _cnt0a, _cnt0b, _cnt1a, _cnt1b, _cnt2a, _cnt2b, _cnt3a, _cnt3b;
	// first
	__m128i a0 = _mm_loadu_si128((const __m128i*)(a));
	__m128i a1 = _mm_loadu_si128((const __m128i*)(a+16));
	__m128i a2 = _mm_loadu_si128((const __m128i*)(a+32));
	__m128i a3 = _mm_loadu_si128((const __m128i*)(a+48));
	__m128i b0 = _mm_loadu_si128((const __m128i*)(b));
	__m128i b1 = _mm_loadu_si128((const __m128i*)(b+16));
	__m128i b2 = _mm_loadu_si128((const __m128i*)(b+32));
	__m128i b3 = _mm_loadu_si128((const __m128i*)(b+48));
	b0 = _mm_xor_si128(a0, b0);
	b1 = _mm_xor_si128(a1, b1);
	b2 = _mm_xor_si128(a2, b2);
	b3 = _mm_xor_si128(a3, b3);
	a0 = _mm_srli_si128(b0,8);
	a1 = _mm_srli_si128(b1,8);
	a2 = _mm_srli_si128(b2,8);
	a3 = _mm_srli_si128(b3,8);
	_dis0a = _mm_cvtsi128_si64(b0);
	_dis0b = _mm_cvtsi128_si64(a0);
	_dis1a = _mm_cvtsi128_si64(b1);
	_dis1b = _mm_cvtsi128_si64(a1);
	_dis2a = _mm_cvtsi128_si64(b2);
	_dis2b = _mm_cvtsi128_si64(a2);
	_dis3a = _mm_cvtsi128_si64(b3);
	_dis3b = _mm_cvtsi128_si64(a3);
	_cnt0a = _mm_popcnt_u64(_dis0a);
	_cnt0b = _mm_popcnt_u64(_dis0b);
	_cnt1a = _mm_popcnt_u64(_dis1a);
	_cnt1b = _mm_popcnt_u64(_dis1b);
	_cnt2a = _mm_popcnt_u64(_dis2a);
	_cnt2b = _mm_popcnt_u64(_dis2b);
	_cnt3a = _mm_popcnt_u64(_dis3a);
	_cnt3b = _mm_popcnt_u64(_dis3b);
	return _cnt0a + _cnt0b + _cnt1a + _cnt1b + _cnt2a + _cnt2b + _cnt3a + _cnt3b;
#endif
}