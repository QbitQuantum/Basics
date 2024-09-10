static void test_gen_random(void)
{
	BOOL result;
	BYTE rnd1[16], rnd2[16];

	memset(rnd1, 0, sizeof(rnd1));
	memset(rnd2, 0, sizeof(rnd2));
	
	result = CryptGenRandom(hProv, sizeof(rnd1), rnd1);
	ok(result, "%08x\n", (unsigned int)GetLastError());

	result = CryptGenRandom(hProv, sizeof(rnd2), rnd2);
	ok(result, "%08x\n", (unsigned int)GetLastError());

	ok(memcmp(rnd1, rnd2, sizeof(rnd1)), "CryptGenRandom generates non random data\n");
}