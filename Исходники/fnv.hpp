meave::vec::AVX avx1(const ::uint8_t *$, ::size_t len) noexcept {
	assert(0 == len % 4);
	meave::vec::AVX hash{ .i8_ = _mm256_set1_epi64(aux::fnv_offset_basis()) };
	meave::vec::AVX prime{ .i8_ = _mm256_set1_epi64(aux::fnv_prime()) };
	for (const ::uint8_t *p = $; len; len-=4) {
		hash.i8_ = _mm256_mul_epi64(hash.i8_, prime);
		meave::vec::AVX x{ .i8_ = _mm256_set_epi64(p[0], p[1], p[2],p[3])};
		hash.i8_ = _mm256_xor_si256(hash.i8_, x.i8_);
	}
	return hash;
}

meave::vec::AVX avx1a(const ::uint8_t *$, ::size_t len) noexcept {
	assert(0 == len % 4);
	meave::vec::AVX hash{ .i8_ = _mm256_set1_epi64(aux::fnv_offset_basis()) };
	meave::vec::AVX prime{ .i8_ = _mm256_set1_epi64(aux::fnv_prime()) };
	for (const ::uint8_t *p = $; len; len-=4) {
		meave::vec::AVX x{ .i8_ = _mm256_set_epi64(p[0], p[1], p[2],p[3])};
		hash.i8_ = _mm256_xor_si256(hash.i8_, x.i8_);
		hash.i8_ = _mm256_mul_epi64(hash.i8_, prime);
	}
	return hash;
}
#endif

} } /* namespace ::meave::fnv */