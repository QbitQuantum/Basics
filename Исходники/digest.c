ZIX_API uint32_t
zix_digest_add(uint32_t hash, const void* const buf, const size_t len)
{
	const uint8_t* str = (const uint8_t*)buf;
#ifdef __SSE4_2__
	// SSE 4.2 CRC32
	for (size_t i = 0; i < (len / sizeof(uint32_t)); ++i) {
		hash = _mm_crc32_u32(hash, *(const uint32_t*)str);
		str += sizeof(uint32_t);
	}
	if (len & sizeof(uint16_t)) {
		hash = _mm_crc32_u16(hash, *(const uint16_t*)str);
		str += sizeof(uint16_t);
	}
	if (len & sizeof(uint8_t)) {
		hash = _mm_crc32_u8(hash, *(const uint8_t*)str);
	}
#else
	// Classic DJB hash
	for (size_t i = 0; i < len; ++i) {
		hash = (hash << 5) + hash + str[i];
	}
#endif
	return hash;
}