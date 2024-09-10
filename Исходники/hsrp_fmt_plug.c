static int crypt_all(int *pcount, struct db_salt *salt)
{
	const int count = *pcount;
	int index = 0;
#ifdef _OPENMP
#pragma omp parallel for
	for (index = 0; index < count; index++)
#endif
	{
		uint32_t block[16] = { 0 };
		int len = saved_len[index];
		MD5_CTX ctx;
		MD5_Init(&ctx);
		// key + keyfill
		memcpy(block, saved_key[index], len);
		PUTCHAR(block, len, 0x80);
		block[14] = len << 3;
#if (ARCH_LITTLE_ENDIAN==0)
		block[14] = JOHNSWAP(block[14]);
#endif
		MD5_Update(&ctx, (unsigned char*)block, 64);
		// data
		MD5_Update(&ctx, cur_salt->salt, cur_salt->length);
		// key (again)
		MD5_Update(&ctx, saved_key[index], len);

		MD5_Final((unsigned char*)crypt_out[index], &ctx);
	}
	return count;
}