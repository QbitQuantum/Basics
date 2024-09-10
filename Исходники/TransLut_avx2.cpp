void	TransLut::process_plane_flt_any_avx2 (uint8_t *dst_ptr, const uint8_t *src_ptr, int stride_dst, int stride_src, int w, int h)
{
	assert (dst_ptr != 0);
	assert (src_ptr != 0);
	assert (stride_dst != 0 || h == 1);
	assert (stride_src != 0 || h == 1);
	assert (w > 0);
	assert (h > 0);

	for (int y = 0; y < h; ++y)
	{
		const FloatIntMix *  s_ptr =
			reinterpret_cast <const FloatIntMix *> (src_ptr);
		TD *                 d_ptr =
			reinterpret_cast <               TD *> (dst_ptr);

		for (int x = 0; x < w; x += 8)
		{
			union
			{
				__m256i            _vect;
				uint32_t           _scal [8];
			}                  index;
			__m256             lerp;
			TransLut_FindIndexAvx2 <M>::find_index (s_ptr + x, index._vect, lerp);
#if 1	// Looks as fast as _mm256_set_ps
			// G++ complains about sizeof() as argument
			__m256             val = _mm256_i32gather_ps (
				&_lut.use <float> (0), index._vect, 4  // 4 == sizeof (float)
			);
			const __m256       va2 = _mm256_i32gather_ps (
				&_lut.use <float> (1), index._vect, 4  // 4 == sizeof (float)
			);
#else
			__m256             val = _mm256_set_ps (
				_lut.use <float> (index._scal [7]    ),
				_lut.use <float> (index._scal [6]    ),
				_lut.use <float> (index._scal [5]    ),
				_lut.use <float> (index._scal [4]    ),
				_lut.use <float> (index._scal [3]    ),
				_lut.use <float> (index._scal [2]    ),
				_lut.use <float> (index._scal [1]    ),
				_lut.use <float> (index._scal [0]    )
			);
			const __m256       va2 = _mm256_set_ps (
				_lut.use <float> (index._scal [7] + 1),
				_lut.use <float> (index._scal [6] + 1),
				_lut.use <float> (index._scal [5] + 1),
				_lut.use <float> (index._scal [4] + 1),
				_lut.use <float> (index._scal [3] + 1),
				_lut.use <float> (index._scal [2] + 1),
				_lut.use <float> (index._scal [1] + 1),
				_lut.use <float> (index._scal [0] + 1)
			);
#endif
			const __m256       dif = _mm256_sub_ps (va2, val);
			val = _mm256_add_ps (val, _mm256_mul_ps (dif, lerp));
			TransLut_store_avx2 (&d_ptr [x], val);
		}

		src_ptr += stride_src;
		dst_ptr += stride_dst;
	}

	_mm256_zeroupper ();	// Back to SSE state
}