void FLAC__precompute_partition_info_sums_intrin_avx2(const FLAC__int32 residual[], FLAC__uint64 abs_residual_partition_sums[],
		uint32_t residual_samples, uint32_t predictor_order, uint32_t min_partition_order, uint32_t max_partition_order, uint32_t bps)
{
	const uint32_t default_partition_samples = (residual_samples + predictor_order) >> max_partition_order;
	uint32_t partitions = 1u << max_partition_order;

	FLAC__ASSERT(default_partition_samples > predictor_order);

	/* first do max_partition_order */
	{
		const uint32_t threshold = 32 - FLAC__bitmath_ilog2(default_partition_samples);
		uint32_t partition, residual_sample, end = (uint32_t)(-(int32_t)predictor_order);

		if(bps + FLAC__MAX_EXTRA_RESIDUAL_BPS < threshold) {
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m128i sum128;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-7; residual_sample+=8) {
					__m256i res256 = _mm256_abs_epi32(_mm256_loadu_si256((const __m256i*)(residual+residual_sample)));
					sum256 = _mm256_add_epi32(sum256, res256);
				}

				sum128 = _mm_add_epi32(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i res128 = _mm_abs_epi32(_mm_loadu_si128((const __m128i*)(residual+residual_sample)));
					sum128 = _mm_add_epi32(sum128, res128);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i res128 = _mm_abs_epi32(_mm_cvtsi32_si128(residual[residual_sample]));
					sum128 = _mm_add_epi32(sum128, res128);
				}

				sum128 = _mm_hadd_epi32(sum128, sum128);
				sum128 = _mm_hadd_epi32(sum128, sum128);
				abs_residual_partition_sums[partition] = (FLAC__uint32)_mm_cvtsi128_si32(sum128);
/* workaround for a bug in MSVC2015U2 - see https://connect.microsoft.com/VisualStudio/feedback/details/2659191/incorrect-code-generation-for-x86-64 */
#if (defined _MSC_VER) && (_MSC_FULL_VER == 190023918) && (defined FLAC__CPU_X86_64)
				abs_residual_partition_sums[partition] &= 0xFFFFFFFF; /**/
#endif
			}
		}
		else { /* have to pessimistically use 64 bits for accumulator */
			for(partition = residual_sample = 0; partition < partitions; partition++) {
				__m256i sum256 = _mm256_setzero_si256();
				__m128i sum128;
				end += default_partition_samples;

				for( ; (int)residual_sample < (int)end-3; residual_sample+=4) {
					__m128i res128 = _mm_abs_epi32(_mm_loadu_si128((const __m128i*)(residual+residual_sample)));
					__m256i res256 = _mm256_cvtepu32_epi64(res128);
					sum256 = _mm256_add_epi64(sum256, res256);
				}

				sum128 = _mm_add_epi64(_mm256_extracti128_si256(sum256, 1), _mm256_castsi256_si128(sum256));

				for( ; (int)residual_sample < (int)end-1; residual_sample+=2) {
					__m128i res128 = _mm_abs_epi32(_mm_loadl_epi64((const __m128i*)(residual+residual_sample)));
					res128 = _mm_cvtepu32_epi64(res128);
					sum128 = _mm_add_epi64(sum128, res128);
				}

				for( ; residual_sample < end; residual_sample++) {
					__m128i res128 = _mm_abs_epi32(_mm_cvtsi32_si128(residual[residual_sample]));
					sum128 = _mm_add_epi64(sum128, res128);
				}

				sum128 = _mm_add_epi64(sum128, _mm_srli_si128(sum128, 8));
				_mm_storel_epi64((__m128i*)(abs_residual_partition_sums+partition), sum128);
			}
		}
	}

	/* now merge partitions for lower orders */
	{
		uint32_t from_partition = 0, to_partition = partitions;
		int partition_order;
		for(partition_order = (int)max_partition_order - 1; partition_order >= (int)min_partition_order; partition_order--) {
			uint32_t i;
			partitions >>= 1;
			for(i = 0; i < partitions; i++) {
				abs_residual_partition_sums[to_partition++] =
					abs_residual_partition_sums[from_partition  ] +
					abs_residual_partition_sums[from_partition+1];
				from_partition += 2;
			}
		}
	}
	_mm256_zeroupper();
}