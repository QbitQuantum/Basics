inline void ClampBufferToS16(s16 *out, const s32 *in, size_t size, s8 volShift) {
#ifdef _M_SSE
	// Size will always be 16-byte aligned as the hwBlockSize is.
	while (size >= 8) {
		__m128i in1 = _mm_loadu_si128((__m128i *)in);
		__m128i in2 = _mm_loadu_si128((__m128i *)(in + 4));
		__m128i packed = _mm_packs_epi32(in1, in2);
		if (useShift) {
			packed = _mm_srai_epi16(packed, volShift);
		}
		_mm_storeu_si128((__m128i *)out, packed);
		out += 8;
		in += 8;
		size -= 8;
	}
#elif PPSSPP_ARCH(ARM_NEON)
	int16x4_t signedVolShift = vdup_n_s16 (-volShift); // Can only dynamic-shift right, but by a signed integer
	while (size >= 8) {
		int32x4_t in1 = vld1q_s32(in);
		int32x4_t in2 = vld1q_s32(in + 4);
		int16x4_t packed1 = vqmovn_s32(in1);
		int16x4_t packed2 = vqmovn_s32(in2);
		if (useShift) {
			packed1 = vshl_s16(packed1, signedVolShift);
			packed2 = vshl_s16(packed2, signedVolShift);
		}
		vst1_s16(out, packed1);
		vst1_s16(out + 4, packed2);
		out += 8;
		in += 8;
		size -= 8;
	}
#endif
	// This does the remainder if SIMD was used, otherwise it does it all.
	for (size_t i = 0; i < size; i++) {
		out[i] = clamp_s16(useShift ? (in[i] >> volShift) : in[i]);
	}
}