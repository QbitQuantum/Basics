rfx_dwt_2d_decode_block_horiz_sse2(INT16* l, INT16* h, INT16* dst, int subband_width)
{
	int y, n;
	INT16* l_ptr = l;
	INT16* h_ptr = h;
	INT16* dst_ptr = dst;
	int first;
	int last;
	__m128i l_n;
	__m128i h_n;
	__m128i h_n_m;
	__m128i tmp_n;
	__m128i dst_n;
	__m128i dst_n_p;
	__m128i dst1;
	__m128i dst2;

	for (y = 0; y < subband_width; y++)
	{
		/* Even coefficients */
		for (n = 0; n < subband_width; n += 8)
		{
			/* dst[2n] = l[n] - ((h[n-1] + h[n] + 1) >> 1); */
			
			l_n = _mm_load_si128((__m128i*) l_ptr);

			h_n = _mm_load_si128((__m128i*) h_ptr);
			h_n_m = _mm_loadu_si128((__m128i*) (h_ptr - 1));

			if (n == 0)
			{
				first = _mm_extract_epi16(h_n_m, 1);
				h_n_m = _mm_insert_epi16(h_n_m, first, 0);
			}
			
			tmp_n = _mm_add_epi16(h_n, h_n_m);
			tmp_n = _mm_add_epi16(tmp_n, _mm_set1_epi16(1));
			tmp_n = _mm_srai_epi16(tmp_n, 1);
			
			dst_n = _mm_sub_epi16(l_n, tmp_n);
			
			_mm_store_si128((__m128i*) l_ptr, dst_n);
			
			l_ptr += 8;
			h_ptr += 8;
		}

		l_ptr -= subband_width;
		h_ptr -= subband_width;
		
		/* Odd coefficients */
		for (n = 0; n < subband_width; n += 8)
		{
			/* dst[2n + 1] = (h[n] << 1) + ((dst[2n] + dst[2n + 2]) >> 1); */
			
			h_n = _mm_load_si128((__m128i*) h_ptr);
			
			h_n = _mm_slli_epi16(h_n, 1);
			
			dst_n = _mm_load_si128((__m128i*) (l_ptr));
			dst_n_p = _mm_loadu_si128((__m128i*) (l_ptr + 1));

			if (n == subband_width - 8)
			{
				last = _mm_extract_epi16(dst_n_p, 6);
				dst_n_p = _mm_insert_epi16(dst_n_p, last, 7);
			}
			
			tmp_n = _mm_add_epi16(dst_n_p, dst_n);
			tmp_n = _mm_srai_epi16(tmp_n, 1);
			
			tmp_n = _mm_add_epi16(tmp_n, h_n);
			
			dst1 = _mm_unpacklo_epi16(dst_n, tmp_n);
			dst2 = _mm_unpackhi_epi16(dst_n, tmp_n);
			
			_mm_store_si128((__m128i*) dst_ptr, dst1);
			_mm_store_si128((__m128i*) (dst_ptr + 8), dst2);
			
			l_ptr += 8;
			h_ptr += 8;
			dst_ptr += 16;
		}
	}
}