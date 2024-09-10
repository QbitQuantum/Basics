int main (int argc, char ** argv)
{
	Skipjack_CTX ctx;
	u8 * adata = "\x33\x22\x11\x00\xdd\xcc\xbb\xaa";
	u8 * akey = "\x00\x99\x88\x77\x66\x55\x44\x33\x22\x11";
	
	u8 digest[8];
	u8 decrypt[8];

	START_ENCRYPT();					
	Skipjack_init(&ctx, akey);
	Encrypt(&ctx, adata, digest);

	START_DECRYPT();
	Skipjack_init(&ctx, akey);
	Decrypt(&ctx, digest, decrypt);

	END_EXPE();
	return 0;
}