inline bool memequal_sse41_wide(const char * p1, const char * p2, size_t size)
{
	__m128i zero16 = _mm_setzero_si128();
//	const char * p1_end = p1 + size;

	while (size >= 64)
	{
		if (_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[0]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[0])))
			&& _mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[1]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[1])))
			&& _mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[2]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[2])))
			&& _mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[3]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[3]))))
		{
			p1 += 64;
			p2 += 64;
			size -= 64;
		}
		else
			return false;
	}

	switch ((size % 64) / 16)
	{
		case 3:
			if (!_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[2]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[2]))))
				return false;
		case 2:
			if (!_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[1]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[1]))))
				return false;
		case 1:
			if (!_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[0]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[0]))))
				return false;
	}

	p1 += (size % 64) / 16 * 16;
	p2 += (size % 64) / 16 * 16;

/*

	if (size >= 32)
	{
		if (_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[0]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[0])))
			& _mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[1]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[1]))))
		{
			p1 += 32;
			p2 += 32;
			size -= 32;
		}
		else
			return false;
	}

	if (size >= 16)
	{
		if (_mm_testc_si128(
				zero16,
				_mm_xor_si128(
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p1)[0]),
					_mm_loadu_si128(&reinterpret_cast<const __m128i *>(p2)[0]))))
		{
			p1 += 16;
			p2 += 16;
			size -= 16;
		}
		else
			return false;
	}*/

	switch (size % 16)
	{
		case 15: if (p1[14] != p2[14]) return false;
		case 14: if (p1[13] != p2[13]) return false;
		case 13: if (p1[12] != p2[12]) return false;
		case 12: if (reinterpret_cast<const UInt32 *>(p1)[2] == reinterpret_cast<const UInt32 *>(p2)[2]) goto l8; else return false;
		case 11: if (p1[10] != p2[10]) return false;
		case 10: if (p1[9] != p2[9]) return false;
		case 9:  if (p1[8] != p2[8]) return false;
	l8: case 8:  return reinterpret_cast<const UInt64 *>(p1)[0] == reinterpret_cast<const UInt64 *>(p2)[0];
		case 7:  if (p1[6] != p2[6]) return false;
		case 6:  if (p1[5] != p2[5]) return false;
		case 5:  if (p1[4] != p2[4]) return false;
		case 4:  return reinterpret_cast<const UInt32 *>(p1)[0] == reinterpret_cast<const UInt32 *>(p2)[0];
		case 3:  if (p1[2] != p2[2]) return false;
		case 2:  return reinterpret_cast<const UInt16 *>(p1)[0] == reinterpret_cast<const UInt16 *>(p2)[0];
		case 1:  if (p1[0] != p2[0]) return false;
		case 0:  break;
	}

	return true;
}