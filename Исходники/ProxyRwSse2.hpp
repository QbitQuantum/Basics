//	const __m128i	mask_lsb = _mm_set1_epi16 (0x00FF);
//	const __m128i	sign_bit = _mm_set1_epi16 (-0x8000);
//	const __m128	offset   = _mm_set1_ps (-32768);
void	ProxyRwSse2 <SplFmt_STACK16>::write_flt (const Ptr::Type &ptr, const __m128 &src0, const __m128 &src1, const __m128i &mask_lsb, const __m128i &sign_bit, const __m128 &offset)
{
	__m128			val_03_f = _mm_add_ps (src0, offset);
	__m128			val_47_f = _mm_add_ps (src1, offset);

	const __m128i	val_03 = _mm_cvtps_epi32 (val_03_f);
	const __m128i	val_47 = _mm_cvtps_epi32 (val_47_f);

	__m128i			val = _mm_packs_epi32 (val_03, val_47);
	val = _mm_xor_si128 (val, sign_bit);

	fstb::ToolsSse2::store_8_16ml (
		ptr._msb_ptr,
		ptr._lsb_ptr,
		val,
		mask_lsb
	);
}