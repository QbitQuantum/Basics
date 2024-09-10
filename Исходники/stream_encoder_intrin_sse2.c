void FLAC__precompute_partition_info_sums_intrin_sse2(const FLAC__int32 residual[], FLAC__uint64 abs_residual_partition_sums[],
		unsigned residual_samples, unsigned predictor_order, unsigned min_partition_order, unsigned max_partition_order, unsigned bps)
{
	const unsigned default_partition_samples = (residual_samples + predictor_order) >> max_partition_order;
	unsigned partitions = 1u << max_partition_order;

	FLAC__ASSERT(default_partition_samples > predictor_order);

	/* first do max_partition_order */
	{
		const unsigned threshold = 32 - FLAC__bitmath_ilog2(default_partition_samples);
		unsigned partition, residual_sample, end = (unsigned)(-(int)predictor_order);

		if(bps + FLAC__MAX_EXTRA_RESIDUAL_BPS < threshold) {
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m128i mm_sum = _mm_setzero_si128();
				unsigned e1, e3;
				end += default_partition_samples;

				e1 = (residual_sample + 3) & ~3; e3 = end & ~3;
				if(e1 > end)
					e1 = end; /* try flac -l 1 -b 16 and you'll be here */

				/* assumption: residual[] is properly aligned so (residual + e1) is properly aligned too and _mm_loadu_si128() is fast */
				for( ; residual_sample < e1; residual_sample++) {
					__m128i mm_res = _mm_cvtsi32_si128(residual[residual_sample]);
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask); /* abs(INT_MIN) is undefined, but if the residual is INT_MIN we have bigger problems */
					mm_sum = _mm_add_epi32(mm_sum, mm_res);
				}

				for( ; residual_sample < e3; residual_sample+=4) {
					__m128i mm_res = _mm_loadu_si128((const __m128i*)(residual+residual_sample));
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask);
					mm_sum = _mm_add_epi32(mm_sum, mm_res);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i mm_res = _mm_cvtsi32_si128(residual[residual_sample]);
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask);
					mm_sum = _mm_add_epi32(mm_sum, mm_res);
				}

				mm_sum = _mm_add_epi32(mm_sum, _mm_srli_si128(mm_sum, 8));
				mm_sum = _mm_add_epi32(mm_sum, _mm_srli_si128(mm_sum, 4));
				abs_residual_partition_sums[partition] = (FLAC__uint32)_mm_cvtsi128_si32(mm_sum);
			}
		}
		else { /* have to pessimistically use 64 bits for accumulator */
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m128i mm_sum = _mm_setzero_si128();
				unsigned e1, e3;
				end += default_partition_samples;

				e1 = (residual_sample + 1) & ~1; e3 = end & ~1;
				FLAC__ASSERT(e1 <= end);

				for( ; residual_sample < e1; residual_sample++) {
					__m128i mm_res = _mm_cvtsi32_si128(residual[residual_sample]); /*  0   0   0   r0 */
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask); /*  0   0   0  |r0|  ==   00   |r0_64| */
					mm_sum = _mm_add_epi64(mm_sum, mm_res);
				}

				for( ; residual_sample < e3; residual_sample+=2) {
					__m128i mm_res = _mm_loadl_epi64((const __m128i*)(residual+residual_sample)); /*  0   0   r1  r0 */
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask); /*  0   0  |r1|   |r0| */
					mm_res = _mm_shuffle_epi32(mm_res, _MM_SHUFFLE(3,1,2,0)); /* 0  |r1|  0  |r0|  ==  |r1_64|  |r0_64|  */
					mm_sum = _mm_add_epi64(mm_sum, mm_res);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i mm_res = _mm_cvtsi32_si128(residual[residual_sample]);
					__m128i mm_mask = _mm_srai_epi32(mm_res, 31);
					mm_res = _mm_xor_si128(mm_res, mm_mask);
					mm_res = _mm_sub_epi32(mm_res, mm_mask);
					mm_sum = _mm_add_epi64(mm_sum, mm_res);
				}

				mm_sum = _mm_add_epi64(mm_sum, _mm_srli_si128(mm_sum, 8));
				_mm_storel_epi64((__m128i*)(abs_residual_partition_sums+partition), mm_sum);
			}
		}
	}

	/* now merge partitions for lower orders */
	{
		unsigned from_partition = 0, to_partition = partitions;
		int partition_order;
		for(partition_order = (int)max_partition_order - 1; partition_order >= (int)min_partition_order; partition_order--) {
			unsigned i;
			partitions >>= 1;
			for(i = 0; i < partitions; i++) {
				abs_residual_partition_sums[to_partition++] =
					abs_residual_partition_sums[from_partition  ] +
					abs_residual_partition_sums[from_partition+1];
				from_partition += 2;
			}
		}
	}
}