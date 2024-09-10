unsigned long
tdb_hash_calc(const char *data, size_t len)
{
#define MUL	sizeof(long)
	int i;
	unsigned long crc0 = 0, crc1 = 0, h;
	unsigned long *d = (unsigned long *)data;
	size_t n = (len / MUL) & ~1UL;

	for (i = 0; i < n; i += 2) {
		/* See linux/arch/x86/crypto/crc32c-intel.c for CRC32C. */
		crc0 = _mm_crc32_u64(crc0, d[i]);
		crc1 = _mm_crc32_u64(crc1, d[i + 1]);
	}

	if (n * MUL + MUL <= len) {
		crc0 = _mm_crc32_u64(crc0, d[n]);
		n++;
	}

	h = (crc1 << 32) | crc0;

	/*
	 * Generate relatively small and dense hash tail values - they are good
	 * for short strings in htrie which uses less significant bits at root,
	 * however collisions are very probable.
	 */
	n *= MUL;
	switch (len - n) {
	case 7:
		h += data[n] * n;
		++n;
	case 6:
		h += data[n] * n;
		++n;
	case 5:
		h += data[n] * n;
		++n;
	case 4:
		h += data[n] * n;
		++n;
	case 3:
		h += data[n] * n;
		++n;
	case 2:
		h += data[n] * n;
		++n;
	case 1:
		h += data[n] * n;
	}

	return h;
#undef MUL
}