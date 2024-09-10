// Hash a string of up to 24 characters
int computeHash(const char* from,size_t l) {
    if (l<=8) {
        return _mm_crc32_u64(0,((uint64_t*)from)[0]<<(64-8*l));
    } else if (l<=16) {
        return _mm_crc32_u64(_mm_crc32_u64(0,((uint64_t*)from)[0]),(((uint64_t*)from)[1])<<(128-8*l));
    } else {
		return _mm_crc32_u64(
					_mm_crc32_u64(
						_mm_crc32_u64(
							0,
							((uint64_t*)from)[0]
						),
						((uint64_t*)from)[1]
					),
					(((uint64_t*)from)[2])<<(128+64-8*l));
	}
	assert(false&&"Missing a case in hash.");
}