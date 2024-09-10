	size_t operator() (StringRef x) const
	{
		const char * pos = x.data;
		size_t size = x.size;

		if (size == 0)
			return 0;

		if (size < 16)
		{
			return hashLessThan16(x.data, x.size);
		}

		const char * end = pos + size;
		const char * end_16 = pos + size / 16 * 16;
		size_t res0 = -1ULL;
		size_t res1 = -1ULL;

		do
		{
			UInt64 word0 = reinterpret_cast<const UInt64 *>(pos)[0];
			UInt64 word1 = reinterpret_cast<const UInt64 *>(pos)[1];
			res0 = _mm_crc32_u64(res0, word0);
			res1 = _mm_crc32_u64(res1, word1);

			pos += 16;
		} while (pos < end_16);

		UInt64 word0 = *reinterpret_cast<const UInt64 *>(end - 8);
		UInt64 word1 = *reinterpret_cast<const UInt64 *>(end - 16);

	/*	return HashLen16(Rotate(word0 - word1, 43) + Rotate(res0, 30) + res1,
			word0 + Rotate(word1 ^ k3, 20) - res0 + size);*/

		res0 = _mm_crc32_u64(res0, word0);
		res1 = _mm_crc32_u64(res1, word1);

		return hashLen16(res0, res1);
	}