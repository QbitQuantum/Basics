bool scanhash_sse2_32(struct thr_info*thr, const unsigned char *pmidstate,
	unsigned char *pdata,
	unsigned char *phash1, unsigned char *phash,
	const unsigned char *ptarget,
	uint32_t max_nonce, uint32_t *last_nonce,
	uint32_t nonce)
{
	uint32_t *hash32 = (uint32_t *)phash;
    uint32_t *nNonce_p = (uint32_t *)(pdata + 76);
    uint32_t m_midstate[8], m_w[16], m_w1[16];
    __m128i m_4w[64] __attribute__ ((aligned (0x100)));
    __m128i m_4hash[64] __attribute__ ((aligned (0x100)));
    __m128i m_4hash1[64] __attribute__ ((aligned (0x100)));
    __m128i offset;
    int i;

	pdata += 64;

    /* Message expansion */
    memcpy(m_midstate, pmidstate, sizeof(m_midstate));
    memcpy(m_w, pdata, sizeof(m_w)); /* The 2nd half of the data */
    memcpy(m_w1, phash1, sizeof(m_w1));
    memset(m_4hash, 0, sizeof(m_4hash));

    /* Transmongrify */
    for (i = 0; i < 16; i++)
        m_4w[i] = _mm_set1_epi32(m_w[i]);

    for (i = 0; i < 16; i++)
        m_4hash1[i] = _mm_set1_epi32(m_w1[i]);

    for (i = 0; i < 64; i++)
	sha256_consts_m128i[i] = _mm_set1_epi32(g_sha256_k[i]);

    offset = _mm_set_epi32(0x3, 0x2, 0x1, 0x0);

    for (;;)
    {
	int j;

	m_4w[3] = _mm_add_epi32(offset, _mm_set1_epi32(nonce));

	/* Some optimization can be done here W.R.T. precalculating some hash */
	CalcSha256_x86 (m_4hash1, m_4w, m_midstate);
	CalcSha256_x86 (m_4hash, m_4hash1, sha256_32init);

	for (j = 0; j < 4; j++) {
	    if (unlikely(((uint32_t *)&(m_4hash[7]))[j] == 0)) {
		/* We found a hit...so check it */
		/* Use the C version for a check... */

		for (i = 0; i < 8; i++) {
		    *(uint32_t *)&(phash)[i<<2] = ((uint32_t *)&(m_4hash[i]))[j];
		}

		if (unlikely(hash32[7] == 0 && fulltest(phash, ptarget))) {
		     nonce += j;
		     *last_nonce = nonce;
		     *nNonce_p = nonce;
		     return true;
		}
	    }
	}

	if (unlikely((nonce >= max_nonce) || thr->work_restart)) {
		*last_nonce = nonce;
		return false;
	}

	nonce += 4;

   }
}