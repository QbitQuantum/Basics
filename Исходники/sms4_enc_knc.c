void sms4_knc_encrypt_init(sms4_key_t *key)
{
	uint64_t value[sizeof(__m512i)/sizeof(uint64_t)];
	int *p = (int *)value;

	for (i = 0; i < 16; i++)
		p[i] = 0xff00;
	mask_ff00 = _mm512_load_epi32(value);

	for (i = 0; i < 16; i++)
		p[i] = 0xffff;
	mask_ffff = _mm512_load_epi32(value);

	for (i = 0; i < 16; i++)
		p[i] = 0xff0000;
	mask_ff0000 = _mm512_load_epi32(value);

	for (i = 0; i < 16; i++)
		p[i] = 0;
	vindex_0s = _mm512_load_epi32(value);

	for (i = 0; i < 16; i++)
		p[i] = 4 * i;
	vindex_4i = _mm512_load_epi32(value);

	sms4_init_sbox32();
}