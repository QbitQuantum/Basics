uint32_t compute_SAD8_SSE4(
	const uint8_t *img_data_L,
	const uint8_t *img_data_R,
	const size_t img_stride,
	const mrpt::utils::TPixelCoord &pt_L,
	const mrpt::utils::TPixelCoord &pt_R)
{
#if RSO_HAS_SSE4
	const uint8_t *ptrL = img_data_L+img_stride*(pt_L.y-3) + (pt_L.x-3);
	const uint8_t *ptrR = img_data_R+img_stride*(pt_R.y-3) + (pt_R.x-3);

	// Refer to the documentation of _mm_mpsadbw_epu8() for details
	// See also: http://software.intel.com/en-us/articles/motion-estimation-with-intel-streaming-simd-extensions-4-intel-sse4/
	const int mask_00 = 0x00;   // SAD of bytes 3:0 of both L&R images
	const int mask_44 = 0x05;   // SAD of bytes 7:4 of both L&R images

	int16_t total_SAD=0;
	for (int y=0;y<8;y++)
	{
		// Load 8 pixels from each image:
		const __m128i imgL = _mm_loadu_si128((const __m128i*)ptrL); // "u" allows 16-unaligned ptrs 
		const __m128i imgR = _mm_loadu_si128((const __m128i*)ptrR); // "u" allows 16-unaligned ptrs 

		// We'll only use the lowest 16bit sum (we are wasting a lot of potential of this instruction!!)
		const __m128i sad00 = _mm_mpsadbw_epu8(imgL,imgR, mask_00);
		const __m128i sad44 = _mm_mpsadbw_epu8(imgL,imgR, mask_44);
		
		total_SAD+= sad00.m128i_i16[0]+sad44.m128i_i16[0];

		ptrL+=img_stride;
		ptrR+=img_stride;
	}
	return total_SAD;
#else
	return 0; // shouldn't ever reach this anyway
#endif
}