void AES_ecb_encrypt_blks_4_in_out(block *in, block *out,  AES_KEY *aesKey) {
	unsigned j, rnds = ROUNDS(aesKey);
	const block *sched = ((block *)(aesKey->rd_key));
	//block temp[4];

	out[0] = _mm_xor_si128(in[0], sched[0]);
	out[1] = _mm_xor_si128(in[1], sched[0]);
	out[2] = _mm_xor_si128(in[2], sched[0]);
	out[3] = _mm_xor_si128(in[3], sched[0]);

	for (j = 1; j < rnds; ++j){
		out[0] = _mm_aesenc_si128(out[0], sched[j]);
		out[1] = _mm_aesenc_si128(out[1], sched[j]);
		out[2] = _mm_aesenc_si128(out[2], sched[j]);
		out[3] = _mm_aesenc_si128(out[3], sched[j]);
	}
	out[0] = _mm_aesenclast_si128(out[0], sched[j]);
	out[1] = _mm_aesenclast_si128(out[1], sched[j]);
	out[2] = _mm_aesenclast_si128(out[2], sched[j]);
	out[3] = _mm_aesenclast_si128(out[3], sched[j]);
}