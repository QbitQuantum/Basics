int haraka256256(unsigned char *hash, const unsigned char *msg) {
	// stuff we need
	int i, j;
	__m128i s[2], tmp, rcon;
	__m128i MSB64 = _mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0,0);

	// set initial round constant
	rcon = _mm_set_epi32(1,1,1,1);

	// initialize state to msg
	s[0] = _mm_load_si128(&((__m128i*)msg)[0]);
	s[1] = _mm_load_si128(&((__m128i*)msg)[1]);

	//printf("= input state =\n");
	//printstate256(s[0], s[1]);

	for (i = 0; i < ROUNDS; ++i) {
		// aes round(s)
		for (j = 0; j < AES_PER_ROUND; ++j) {
			s[0] = _mm_aesenc_si128(s[0], rcon);
			s[1] = _mm_aesenc_si128(s[1], rcon);
			rcon = _mm_slli_epi32(rcon, 1);
		}

		//printf("= round %d : after aes layer =\n", i);
		//printstate256(s[0], s[1]);
		
		// mixing
		tmp = _mm_unpacklo_epi32(s[0], s[1]);
		s[1] = _mm_unpackhi_epi32(s[0], s[1]);
		s[0] = tmp;

		//printf("= round %d : after mix layer =\n", i);
		//printstate256(s[0], s[1]);
	}

	//printf("= output from permutation =\n");
	//printstate256(s[0], s[1]);

	// xor message to get DM effect
	s[0] = _mm_xor_si128(s[0], _mm_load_si128(&((__m128i*)msg)[0]));
	s[1] = _mm_xor_si128(s[1], _mm_load_si128(&((__m128i*)msg)[1]));

	//printf("= after feed-forward =\n");
	//printstate256(s[0], s[1]);

	// store result
	_mm_storeu_si128((__m128i*)hash, s[0]);
	_mm_storeu_si128((__m128i*)(hash + 16), s[1]);
}