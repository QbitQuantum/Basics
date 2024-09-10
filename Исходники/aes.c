inline void AES_set_decrypt_key_fast(AES_KEY *dkey, const AES_KEY *ekey) {
	int j = 0;
	int i = ROUNDS(ekey);
#if (OCB_KEY_LEN == 0)
	dkey->rounds = i;
#endif
	dkey->rd_key[i--] = ekey->rd_key[j++];
	while (i)
		dkey->rd_key[i--] = _mm_aesimc_si128(ekey->rd_key[j++]);
	dkey->rd_key[i] = ekey->rd_key[j];
}