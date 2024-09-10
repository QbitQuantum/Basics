void serpent256_set_key(const unsigned char *key, serpent256_key *skey)
{
	unsigned long W[140], i;

	__movsb((unsigned char*)&W, key, SERPENT_KEY_SIZE);

	for(i = 8; i != 140; ++i) {
		W[i] = _rotl(W[i-8] ^ W[i-5] ^ W[i-3] ^ W[i-1] ^ PHI ^ (i-8), 11);
	}
	for (i = 8; i <= 136; i += 4) {
		se_tab[7 - (((i / 4) + 2) % 8)](&W[i]);
	}
	__movsb((unsigned char*)&skey->expkey, (unsigned char*)(W+8), (SERPENT_EXPKEY_WORDS * sizeof(unsigned long)));
}