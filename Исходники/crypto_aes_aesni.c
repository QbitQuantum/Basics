/**
 * crypto_aes_encrypt_block_aesni(in, out, key):
 * Using the expanded AES key ${key}, encrypt the block ${in} and write the
 * resulting ciphertext to ${out}.  This implementation uses x86 AESNI
 * instructions, and should only be used if CPUSUPPORT_X86_AESNI is defined
 * and cpusupport_x86_aesni() returns nonzero.
 */
void
crypto_aes_encrypt_block_aesni(const uint8_t * in, uint8_t * out,
    const void * key)
{
	const struct crypto_aes_key_aesni * _key = key;
	const __m128i * aes_key = _key->rkeys;
	__m128i aes_state;
	size_t nr = _key->nr;

	aes_state = _mm_loadu_si128((const __m128i *)in);
	aes_state = _mm_xor_si128(aes_state, aes_key[0]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[1]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[2]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[3]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[4]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[5]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[6]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[7]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[8]);
	aes_state = _mm_aesenc_si128(aes_state, aes_key[9]);
	if (nr > 10) {
		aes_state = _mm_aesenc_si128(aes_state, aes_key[10]);
		aes_state = _mm_aesenc_si128(aes_state, aes_key[11]);

		if (nr > 12) {
			aes_state = _mm_aesenc_si128(aes_state, aes_key[12]);
			aes_state = _mm_aesenc_si128(aes_state, aes_key[13]);
		}
	}

	aes_state = _mm_aesenclast_si128(aes_state, aes_key[nr]);
	_mm_storeu_si128((__m128i *)out, aes_state);
}