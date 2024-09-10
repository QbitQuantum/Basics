inline void casefoldRange(char* dest, const char* begin, const char* end)
{
	if (end - begin < 64)
	{
		// short string, don't bother optimizing
		for (const char* i = begin; i != end; ++i)
			*dest++ = casefold(*i);
	}
	else
	{
		// Shift 'A'..'Z' range ([65..90]) to [102..127] to use one signed comparison insn
		__m128i shiftAmount = _mm_set1_epi8(127 - 'Z');
		__m128i lowerBound = _mm_set1_epi8(127 - ('Z' - 'A') - 1);
		__m128i upperBit = _mm_set1_epi8(0x20);

		const char* i = begin;

		for (; i + 16 < end; i += 16)
		{
			__m128i v = _mm_loadu_si128(reinterpret_cast<const __m128i*>(i));
			__m128i upperMask = _mm_cmpgt_epi8(_mm_add_epi8(v, shiftAmount), lowerBound);
			__m128i cfv = _mm_or_si128(v, _mm_and_si128(upperMask, upperBit));
			_mm_storeu_si128(reinterpret_cast<__m128i*>(dest), cfv);
			dest += 16;
		}

		for (; i != end; ++i)
			*dest++ = casefold(*i);
	}
}