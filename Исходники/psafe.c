int main(int argc, char **argv)
{
	int ret;
	setlocale(LC_ALL, "");

	if (argc != 3) {
		wprintf(L"Usage: psafe file.psafe3 passphrase");
		exit(EXIT_FAILURE);
	}

	init_crypto(64*1024);

	size_t sz;
	uint8_t *ptr;
	ptr = mapfile_ro(argv[1], &sz);
	if (ptr == NULL)
		err(1, "%s", argv[1]);

	struct psafe3_pro *pro;
	pro = (struct psafe3_pro *)(ptr + 4);
	struct safe_sec *sec;
	sec = gcry_malloc_secure(sizeof(*sec));
	ret = stretch_and_check_pass(argv[2], strlen(argv[2]), pro, sec);
	if (ret != 0) {
		gcry_free(sec);
		wprintf(L"Invalid password.\n");
		exit(1);
	}

	uint8_t *safe;
	size_t safe_size;
	safe_size = sz - (4 + sizeof(*pro) + 48);
	assert(safe_size > 0);
	assert(safe_size % TWOF_BLKSIZE == 0);
	safe = gcry_malloc_secure(safe_size);
	assert(safe != NULL);

	gcry_error_t gerr;
	struct decrypt_ctx ctx;
	if (init_decrypt_ctx(&ctx, pro, sec) < 0)
		gcrypt_fatal(ctx.gerr);

	size_t bcnt;
	bcnt = safe_size / TWOF_BLKSIZE;
	assert(bcnt > 0);
	uint8_t *encp;
	uint8_t *safep;
	encp = ptr + 4 + sizeof(*pro);
	safep = safe;
	while (bcnt--) {
		gerr = gcry_cipher_decrypt(ctx.cipher, safep, TWOF_BLKSIZE, encp, TWOF_BLKSIZE);
		if (gerr != GPG_ERR_NO_ERROR)
			gcrypt_fatal(gerr);
		safep += TWOF_BLKSIZE;
		encp += TWOF_BLKSIZE;
	}

	enum { HDR, DB };
	int state = HDR;
	safep = safe;
	while (safep < safe + safe_size) {
		struct field *fld;
		fld = (struct field *)safep;
		wprintf(L"len=%-3u  type=%02x  ", fld->len, fld->type);
		if (state == DB)
			db_print(stdout, fld);
		else
			hd_print(stdout, fld);
		if (fld->type == 0xff)
			state = DB;
		putwc('\n', stdout);
		if (fld->len)
			gcry_md_write(ctx.hmac, safep + sizeof(*fld), fld->len);
		safep += ((fld->len + 5 + 15) / TWOF_BLKSIZE) * TWOF_BLKSIZE;
	}

	assert(memcmp(ptr + (sz - 48), "PWS3-EOFPWS3-EOF", TWOF_BLKSIZE) == 0);

#define EOL() putwc('\n', stdout)
	EOL();
	print_prologue(stdout, pro);
	wprintf(L"KEY    "); printhex(stdout, sec->pprime, 32); EOL();
	wprintf(L"H(KEY) "); printhex(stdout, pro->h_pprime, 32); EOL();

	gcry_md_final(ctx.hmac);
	wprintf(L"HMAC'  ");
	uint8_t hmac[32];
	memmove(hmac, gcry_md_read(ctx.hmac, GCRY_MD_SHA256), 32);
	printhex(stdout, hmac, 32);
	EOL();

	wprintf(L"HMAC   ");
	printhex(stdout, ptr + (sz - 32), 32);
	EOL();
#undef EOL

	gcry_free(safe);
	gcry_free(sec);
	unmapfile(ptr, sz);
	term_decrypt_ctx(&ctx);

	exit(0);
}