DWORD WINAPI Autotune::AutotuneThread(void *i)
//--------------------------------------------
{
	AutotuneThreadData &info = *static_cast<AutotuneThreadData *>(i);
	info.histogram.resize(HISTORY_BINS, 0);
#ifdef ENABLE_SSE2
	const bool useSSE = (GetProcSupport() & PROCSUPPORT_SSE2) != 0;
#endif

	// Do autocorrelation and save results in a note histogram (restriced to one octave).
	for(int note = info.startNote, noteBin = note; note < info.endNote; note++, noteBin++)
	{

		if(noteBin >= HISTORY_BINS)
		{
			noteBin %= HISTORY_BINS;
		}

		const SmpLength autocorrShift = NoteToShift(info.sampleFreq, note, info.pitchReference);

		uint64 autocorrSum = 0;

#ifdef ENABLE_SSE2
		if(useSSE)
		{
			const __m128i *normalData = reinterpret_cast<const __m128i *>(info.sampleData);
			const __m128i *shiftedData = reinterpret_cast<const __m128i *>(info.sampleData + autocorrShift);
			for(SmpLength i = info.processLength / 8; i != 0; i--)
			{
				__m128i normal = _mm_loadu_si128(normalData++);
				__m128i shifted = _mm_loadu_si128(shiftedData++);
				__m128i diff = _mm_sub_epi16(normal, shifted);		// 8 16-bit differences
				__m128i squares = _mm_madd_epi16(diff, diff);		// Multiply and add: 4 32-bit squares

				__m128i sum1 = _mm_shuffle_epi32(squares, _MM_SHUFFLE(0, 1, 2, 3));	// Move upper two integers to lower
				__m128i sum2  = _mm_add_epi32(squares, sum1);						// Now we can add the (originally) upper two and lower two integers
				__m128i sum3 = _mm_shuffle_epi32(sum2, _MM_SHUFFLE(1, 1, 1, 1));	// Move the second-lowest integer to lowest position
				__m128i sum4  = _mm_add_epi32(sum2, sum3);							// Add the two lowest positions
				autocorrSum += _mm_cvtsi128_si32(sum4);
			}
		} else
#endif
		{
			const int16 *normalData = info.sampleData;
			const int16 *shiftedData = info.sampleData + autocorrShift;
			// Add up squared differences of all values
			for(SmpLength i = info.processLength; i != 0; i--, normalData++, shiftedData++)
			{
				autocorrSum += (*normalData - *shiftedData) * (*normalData - *shiftedData);
			}
		}

		info.histogram[noteBin] += autocorrSum;
	}
	return 0;
}