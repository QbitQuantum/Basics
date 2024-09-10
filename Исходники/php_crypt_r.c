char * php_md5_crypt_r(const char *pw, const char *salt, char *out) {
	HCRYPTPROV hCryptProv;
	HCRYPTHASH ctx, ctx1;
	unsigned int i, pwl, sl;
	const BYTE magic_md5[4] = "$1$";
	const DWORD magic_md5_len = 3;
	DWORD        dwHashLen;
	int pl;
	__int32 l;
	const char *sp = salt;
	const char *ep = salt;
	char *p = NULL;
	char *passwd = out;
	unsigned char final[16];

	/* Acquire a cryptographic provider context handle. */
	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		return NULL;
	}

	pwl = (unsigned int) strlen(pw);

	/* Refine the salt first */
	sp = salt;

	/* If it starts with the magic string, then skip that */
	if (strncmp(sp, MD5_MAGIC, MD5_MAGIC_LEN) == 0) {
		sp += MD5_MAGIC_LEN;
	}

	/* It stops at the first '$', max 8 chars */
	for (ep = sp; *ep != '\0' && *ep != '$' && ep < (sp + 8); ep++) {
		continue;
	}

	/* get the length of the true salt */
	sl = ep - sp;

	/* Create an empty hash object. */
	if(!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &ctx)) {
		goto _destroyProv;
	}

	/* The password first, since that is what is most unknown */
	if(!CryptHashData(ctx, (BYTE *)pw, pwl, 0)) {
		goto _destroyCtx0;
	}

	/* Then our magic string */
	if(!CryptHashData(ctx, magic_md5, magic_md5_len, 0)) {
		goto _destroyCtx0;
	}

	/* Then the raw salt */
	if(!CryptHashData( ctx, (BYTE *)sp, sl, 0)) {
		goto _destroyCtx0;
	}

	/* MD5(pw,salt,pw), valid. */
	/* Then just as many characters of the MD5(pw,salt,pw) */
	if(!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &ctx1)) {
		goto _destroyCtx0;
	}
	if(!CryptHashData(ctx1, (BYTE *)pw, pwl, 0)) {
		goto _destroyCtx1;
	}
	if(!CryptHashData(ctx1, (BYTE *)sp, sl, 0)) {
		goto _destroyCtx1;
	}
	if(!CryptHashData(ctx1, (BYTE *)pw, pwl, 0)) {
		goto _destroyCtx1;
	}

	dwHashLen = 16;
	CryptGetHashParam(ctx1, HP_HASHVAL, final, &dwHashLen, 0);
	/*  MD5(pw,salt,pw). Valid. */

	for (pl = pwl; pl > 0; pl -= 16) {
		CryptHashData(ctx, final, (DWORD)(pl > 16 ? 16 : pl), 0);
	}

	/* Don't leave anything around in vm they could use. */
	memset(final, 0, sizeof(final));

	/* Then something really weird... */
	for (i = pwl; i != 0; i >>= 1) {
		if ((i & 1) != 0) {
			CryptHashData(ctx, (const BYTE *)final, 1, 0);
		} else {