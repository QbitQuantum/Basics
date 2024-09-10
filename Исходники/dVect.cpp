// count genotype sum and number of calls, not requiring 16-aligned p
COREARRAY_DLL_DEFAULT C_UInt8* vec_u8_geno_count(C_UInt8 *p,
	size_t n, C_Int32 &out_sum, C_Int32 &out_num)
{
	C_Int32 sum=0, num=0;

#if defined(COREARRAY_SIMD_AVX2)

	const __m256i three = _mm256_set1_epi8(3);
	const __m256i zero = _mm256_setzero_si256();
	__m256i sum32 = zero, num32 = zero;
	size_t limit_by_U8 = 0;

	for (; n >= 32; )
	{
		__m256i v = _mm256_loadu_si256((__m256i const*)p);
		p += 32;
		__m256i m = _mm256_cmpgt_epi8(three, _mm256_min_epu8(v, three));
		sum32 = _mm256_add_epi8(sum32, _mm256_and_si256(v, m));
		num32 = _mm256_sub_epi8(num32, m);
		n -= 32;
		limit_by_U8 ++;
		if ((limit_by_U8 >= 127) || (n < 32))
		{
			// add to sum
			sum32 = _mm256_sad_epu8(sum32, zero);
			sum32 = _mm256_add_epi32(sum32,
				_mm256_permute4x64_epi64(sum32, _MM_SHUFFLE(1,0,3,2)));
			sum32 = _mm256_add_epi32(sum32,
				_mm256_permute4x64_epi64(sum32, _MM_SHUFFLE(0,0,0,1)));
			sum += _mm_cvtsi128_si32(_mm256_castsi256_si128(sum32));
			// add to num
			num32 = _mm256_sad_epu8(num32, zero);
			num32 = _mm256_add_epi32(num32,
				_mm256_permute4x64_epi64(num32, _MM_SHUFFLE(1,0,3,2)));
			num32 = _mm256_add_epi32(num32,
				_mm256_permute4x64_epi64(num32, _MM_SHUFFLE(0,0,0,1)));
			num += _mm_cvtsi128_si32(_mm256_castsi256_si128(num32));
			// reset
			sum32 = num32 = zero;
			limit_by_U8 = 0;
		}
	}

#elif defined(COREARRAY_SIMD_SSE2)

	// header, 16-byte aligned
	size_t h = (16 - ((size_t)p & 0x0F)) & 0x0F;
	for (; (n > 0) && (h > 0); n--, h--, p++)
		if (*p <= 2) { sum += *p; num++; }

	const __m128i three = _mm_set1_epi8(3);
	const __m128i zero = _mm_setzero_si128();
	__m128i sum16=zero, num16=zero;
	size_t limit_by_U8 = 0;

	for (; n >= 16; )
	{
		__m128i v = _mm_load_si128((__m128i const*)p);
		p += 16;
		__m128i m = _mm_cmpgt_epi8(three, _mm_min_epu8(v, three));
		sum16 = _mm_add_epi8(sum16, v & m);
		num16 = _mm_sub_epi8(num16, m);
		n -= 16;
		limit_by_U8 ++;
		if ((limit_by_U8 >= 127) || (n < 16))
		{
			// add to sum
			sum16 = _mm_sad_epu8(sum16, zero);
			sum += _mm_cvtsi128_si32(sum16);
			sum += _mm_cvtsi128_si32(_mm_shuffle_epi32(sum16, 2));
			// add to num
			num16 = _mm_sad_epu8(num16, zero);
			num += _mm_cvtsi128_si32(num16);
			num += _mm_cvtsi128_si32(_mm_shuffle_epi32(num16, 2));
			// reset
			sum16 = num16 = zero;
			limit_by_U8 = 0;
		}
	}

#endif

	for (; n > 0; n--, p++)
		if (*p <= 2) { sum += *p; num++; }
	out_sum = sum;
	out_num = num;
	return p;
}