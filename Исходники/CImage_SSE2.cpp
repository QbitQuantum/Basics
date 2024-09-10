/** Average each 2x2 pixels into 1x1 pixel (arithmetic average)
  *  - <b>Input format:</b> uint8_t, 1 channel
  *  - <b>Output format:</b> uint8_t, 1 channel
  *  - <b>Preconditions:</b> in & out aligned to 16bytes, w = k*16 (w=width in pixels), widthStep=w*1
  *  - <b>Notes:</b>
  *  - <b>Requires:</b> SSE2
  *  - <b>Invoked from:</b> mrpt::utils::CImage::scaleHalfSmooth()
  */
void image_SSE2_scale_half_smooth_1c8u(const uint8_t* in, uint8_t* out, int w, int h)
{
	MRPT_ALIGN16 const unsigned long long mask[2] = {0x00FF00FF00FF00FFull, 0x00FF00FF00FF00FFull};
	const uint8_t* nextRow = in + w;
	__m128i m = _mm_load_si128((const __m128i*)mask);
	int sw = w >> 4;
	int sh = h >> 1;

	for (int i=0; i<sh; i++)
	{
		for (int j=0; j<sw; j++)
		{
			__m128i here = _mm_load_si128((const __m128i*)in);
			__m128i next = _mm_load_si128((const __m128i*)nextRow);
			here = _mm_avg_epu8(here,next);
			next = _mm_and_si128(_mm_srli_si128(here,1), m);
			here = _mm_and_si128(here,m);
			here = _mm_avg_epu16(here, next);
			_mm_storel_epi64((__m128i*)out, _mm_packus_epi16(here,here));
			in += 16;
			nextRow += 16;
			out += 8;
		}

		in += w;
		nextRow += w;
	}
}