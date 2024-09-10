static SRP_Result fill_buff()
{
	g_rand_idx = 0;

#ifdef WIN32
	HCRYPTPROV wctx;
#else
	FILE *fp = 0;
#endif

#ifdef WIN32

	if (!CryptAcquireContext(&wctx, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		return SRP_ERR;
	if (!CryptGenRandom(wctx, sizeof(g_rand_buff), (BYTE *)g_rand_buff)) return SRP_ERR;
	if (!CryptReleaseContext(wctx, 0)) return SRP_ERR;

#else
	fp = fopen("/dev/urandom", "r");

	if (!fp) return SRP_ERR;

	if (fread(g_rand_buff, sizeof(g_rand_buff), 1, fp) != 1) { fclose(fp); return SRP_ERR; }
	if (fclose(fp)) return SRP_ERR;
#endif
	return SRP_OK;
}