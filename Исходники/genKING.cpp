	void thread_ibs_num(size_t i, size_t n)
	{
		const size_t npack  = nBlock >> 3;
		const size_t npack2 = npack * 2;

		C_UInt8 *Base = Geno1b.Get();
		IdMatTri I = Array_Thread_MatIdx[i];
		C_Int64 N = Array_Thread_MatCnt[i];
		TS_KINGHomo *p = ptrKING + I.Offset();

		for (; N > 0; N--, ++I, p++)
		{
			C_UInt8 *p1 = Base + I.Row() * npack2;
			C_UInt8 *p2 = Base + I.Column() * npack2;
			double *pAF  = AF_1_AF.Get();
			double *pAF2 = AF_1_AF_2.Get();
			ssize_t m = npack;

		#if defined(COREARRAY_SIMD_SSE2)
		{
			POPCNT_SSE2_HEAD
			__m128i ibs0_sum, sumsq_sum;
			ibs0_sum = sumsq_sum = _mm_setzero_si128();
			__m128d sq_sum, sq_sum2;
			sq_sum = sq_sum2 = _mm_setzero_pd();

			for (; m > 0; m-=16)
			{
				__m128i g1_1 = _mm_load_si128((__m128i*)p1);
				__m128i g1_2 = _mm_load_si128((__m128i*)(p1 + npack));
				__m128i g2_1 = _mm_load_si128((__m128i*)p2);
				__m128i g2_2 = _mm_load_si128((__m128i*)(p2 + npack));
				p1 += 16; p2 += 16;

				__m128i mask = (g1_1 | ~g1_2) & (g2_1 | ~g2_2);
				__m128i ibs0 = (~((g1_1 ^ ~g2_1) | (g1_2 ^ ~g2_2))) & mask;
				__m128i het  = ((g1_1 ^ g1_2) ^ (g2_1 ^ g2_2)) & mask;

				POPCNT_SSE2_RUN(ibs0)
				ibs0_sum = _mm_add_epi32(ibs0_sum, ibs0);

				POPCNT_SSE2_RUN(het)
				sumsq_sum = _mm_add_epi32(_mm_add_epi32(sumsq_sum, het),
					_mm_slli_epi32(ibs0, 2));

				C_UInt64 m1 = _mm_cvtsi128_si64(mask);
				C_UInt64 m2 = _mm_cvtsi128_si64(_mm_shuffle_epi32(mask,
					 _MM_SHUFFLE(1,0,3,2)));
				for (size_t k=32; k > 0; k--)
				{
					switch (m1 & 0x03)
					{
					case 3:
						sq_sum = _mm_add_pd(sq_sum, _mm_load_pd(pAF));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_load_pd(pAF2));
						break;
					case 1:
						sq_sum = _mm_add_pd(sq_sum, _mm_set_pd(0, pAF[0]));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_set_pd(0, pAF2[0]));
						break;
					case 2:
						sq_sum = _mm_add_pd(sq_sum, _mm_set_pd(pAF[1], 0));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_set_pd(pAF2[1], 0));
						break;
					}
					pAF += 2; pAF2 += 2; m1 >>= 2;
				}
				for (size_t k=32; k > 0; k--)
				{
					switch (m2 & 0x03)
					{
					case 3:
						sq_sum = _mm_add_pd(sq_sum, _mm_load_pd(pAF));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_load_pd(pAF2));
						break;
					case 1:
						sq_sum = _mm_add_pd(sq_sum, _mm_set_pd(0, pAF[0]));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_set_pd(0, pAF2[0]));
						break;
					case 2:
						sq_sum = _mm_add_pd(sq_sum, _mm_set_pd(pAF[1], 0));
						sq_sum2 = _mm_add_pd(sq_sum2, _mm_set_pd(pAF2[1], 0));
						break;
					}
					pAF += 2; pAF2 += 2; m2 >>= 2;
				}
			}

			p->IBS0  += vec_sum_i32(ibs0_sum);
			p->SumSq += vec_sum_i32(sumsq_sum);
			p->SumAFreq += vec_sum_f64(sq_sum);
			p->SumAFreq2 += vec_sum_f64(sq_sum2);
		}
		#else
			for (; m > 0; m-=8)
			{
				C_UInt64 g1_1 = *((C_UInt64*)p1);
				C_UInt64 g1_2 = *((C_UInt64*)(p1 + npack));
				C_UInt64 g2_1 = *((C_UInt64*)p2);
				C_UInt64 g2_2 = *((C_UInt64*)(p2 + npack));
				p1 += 8; p2 += 8;

				C_UInt64 mask = (g1_1 | ~g1_2) & (g2_1 | ~g2_2);
				C_UInt64 ibs0 = (~((g1_1 ^ ~g2_1) | (g1_2 ^ ~g2_2))) & mask;
				C_UInt64 het  = ((g1_1 ^ g1_2) ^ (g2_1 ^ g2_2)) & mask;

				p->IBS0  += POPCNT_U64(ibs0);
				p->SumSq += POPCNT_U64(het) + POPCNT_U64(ibs0)*4;

				double sum=0, sum2=0;
				for (size_t k=64; k > 0; k--)
				{
					if (mask & 0x01)
						{ sum += (*pAF); sum2 += (*pAF2); }
					pAF ++; pAF2 ++;
					mask >>= 1;
				}
				p->SumAFreq += sum;
				p->SumAFreq2 += sum2;
			}
		#endif
		}
	}