static void
check(u1 *plain, u1 *cipher, u1 *key, int Nk, char *title)
{
	void	*ctx;
	u1	data[Nb * 4];

	MEMCPY(data, plain, Nb * 4);
	ctx = AES_Init(key, Nk);
	if(ctx == NULL) {
		printf("no memory\n");
		return;
	}
	AES_Cipher(ctx, data);
	ps(data);
	if(MEMCMP(data, cipher, Nb * 4))
		printf("%s-cipher is wrong\n", title);

	MEMCPY(data, cipher, Nb * 4);
	AES_InvCipher(ctx, data);
	ps(data);
	if(MEMCMP(data, plain, Nb * 4))
		printf("%s-invcipher is wrong\n", title);
	AES_Finish(ctx);
}