__m256i	Scaler::process_vect_int_avx2 (const __m256i &add_cst, int kernel_size, const __m256i coef_base_ptr [], typename SRC::PtrConst::Type pix_ptr, const __m256i &zero, int src_stride, const __m256i &sign_bit, int len)
{
	typedef typename SRC::template S16 <false, (SB == 16)> SrcS16R;

	__m256i        sum0 = add_cst;
	__m256i        sum1 = add_cst;

	for (int k = 0; k < kernel_size; ++k)
	{
		const __m256i  coef = _mm256_load_si256 (coef_base_ptr + k);
		const __m256i  src  = ReadWrapperInt <SRC, SrcS16R, PF>::read (
			pix_ptr, zero, sign_bit, len
		);

		fstb::ToolsAvx2::mac_s16_s16_s32 (sum0, sum1, src, coef);

		SRC::PtrConst::jump (pix_ptr, src_stride);
	}

	sum0 = _mm256_srai_epi32 (sum0, SHIFT_INT + SB - DB);
	sum1 = _mm256_srai_epi32 (sum1, SHIFT_INT + SB - DB);

	const __m256i  val = _mm256_packs_epi32 (sum0, sum1);

	return (val);
}