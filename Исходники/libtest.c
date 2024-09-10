void test_sio3(void) {
	FILE	*f;
	static char	buf[1024];
	int	i, j;

	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-5");
		return;
	}
	pr("fwrite");
	for (i=31; i<=527; i += 31) {
		memset(buf, i, i);
		if (fwrite(buf, 1, i, f) != i)
			fail("fwrite-1");
	}
	rewind(f);
	pr("fread");
	for (i=31; i<=527; i += 31) {
		memset(buf, i, i);
		if (fread(buf, 1, i, f) != i)
			fail("fread-1");
		for (j=0; j<i; j++) {
			if ((buf[j] & 0xFF) != i % 256)
				break;
		}
		if (j < i) {
			fail("fread-2");
			break;
		}
	}

	if (fclose(f)) fail("fclose-5");

	if ((f = fopen(TMPFILE, "w+")) == NULL) {
		fail("fopen-5");
		return;
	}
	for (i=0; i<1024; i++)
		buf[i] = '5';
	for (i=0; i<16; i++) {
		if (fwrite(buf, 1, 1024, f) != 1024) {
			fail("fwrite-2");
			break;
		}
	}
	rewind(f);
	for (i=0; i<16; i++) {
		if (fread(buf, 1, 1024, f) != 1024) {
			fail("fread-3");
			break;
		}
	}
	if (fgetc(f) != EOF) fail("fread-4");

	clearerr(f);
	rewind(f);
	pr("fseek/ftell");
	if (fseek(f, 0, SEEK_END)) fail("fseek-1");
	if (ftell(f) != 16384) fail("ftell-1");
	if (fseek(f, 8100, SEEK_SET)) fail("fseek-2");
	if (ftell(f) != 8100) fail("fseek-3");
	if (fseek(f, 1900, SEEK_CUR)) fail("fseek-4");
	if (ftell(f) != 10000) fail("fseek-5");

	fclose(f);
	unlink(TMPFILE);
}