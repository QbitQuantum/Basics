static void
md2_compress(MD2Context *cx)
{
	int j;
	unsigned char P;
	P = cx->checksum[MD2_CHECKSUM_SIZE-1];
	/* Compute the running checksum, and set the tmp variables to be 
	 * CV[i] XOR input[i] 
	 */
#define CKSUMFN(n) \
	P = cx->checksum[n] ^ MD2S[cx->X[MD2_INPUT+n] ^ P]; \
	cx->checksum[n] = P; \
	cx->X[MD2_TMPVARS+n] = cx->X[n] ^ cx->X[MD2_INPUT+n];
	CKSUMFN(0);
	CKSUMFN(1);
	CKSUMFN(2);
	CKSUMFN(3);
	CKSUMFN(4);
	CKSUMFN(5);
	CKSUMFN(6);
	CKSUMFN(7);
	CKSUMFN(8);
	CKSUMFN(9);
	CKSUMFN(10);
	CKSUMFN(11);
	CKSUMFN(12);
	CKSUMFN(13);
	CKSUMFN(14);
	CKSUMFN(15);
	/* The compression function. */
#define COMPRESS(n) \
	P = cx->X[n] ^ MD2S[P]; \
	cx->X[n] = P;
	P = 0x00;
	for (j=0; j<18; j++) {
		COMPRESS(0);
		COMPRESS(1);
		COMPRESS(2);
		COMPRESS(3);
		COMPRESS(4);
		COMPRESS(5);
		COMPRESS(6);
		COMPRESS(7);
		COMPRESS(8);
		COMPRESS(9);
		COMPRESS(10);
		COMPRESS(11);
		COMPRESS(12);
		COMPRESS(13);
		COMPRESS(14);
		COMPRESS(15);
		COMPRESS(16);
		COMPRESS(17);
		COMPRESS(18);
		COMPRESS(19);
		COMPRESS(20);
		COMPRESS(21);
		COMPRESS(22);
		COMPRESS(23);
		COMPRESS(24);
		COMPRESS(25);
		COMPRESS(26);
		COMPRESS(27);
		COMPRESS(28);
		COMPRESS(29);
		COMPRESS(30);
		COMPRESS(31);
		COMPRESS(32);
		COMPRESS(33);
		COMPRESS(34);
		COMPRESS(35);
		COMPRESS(36);
		COMPRESS(37);
		COMPRESS(38);
		COMPRESS(39);
		COMPRESS(40);
		COMPRESS(41);
		COMPRESS(42);
		COMPRESS(43);
		COMPRESS(44);
		COMPRESS(45);
		COMPRESS(46);
		COMPRESS(47);
		P = (P + j) % 256;
	}
	cx->unusedBuffer = MD2_BUFSIZE;
}