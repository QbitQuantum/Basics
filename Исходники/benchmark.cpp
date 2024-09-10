int main(int argc, char **argv) {
	if(argc < 2) {
		printf("USAGE: benchmark FILE\n");
		return 1;
	}

	byte key[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint keySize = 16;

	uint *ct, *pt;
	
	FILE *f = fopen(argv[1], "rb");
	if(f == NULL) {
		printf("File not found.\n");
		return 1;
	}

	fseek(f, 0, SEEK_END);
	uint f_size = ftell(f);
	rewind(f);

	if(f_size % 4*sizeof(uint) != 0) {
		printf("Plaintext size must be a multiple of AES block size.\n");
		return 1;
	}

	uint ptSize = f_size / sizeof(uint);
	
	pt = (uint*)malloc(f_size);
	fread(pt, sizeof(uint), ptSize, f);
	fclose(f);

	ct = (uint *)malloc(ptSize*sizeof(uint));

	AES *aes = new AES();
	aes->makeKey(key, keySize << 3, DIR_ENCRYPT);

	clock_t start = clock();
	for(uint i = 0; i < ptSize; i += 4) {
		aes->encrypt(pt + i, ct + i);
	}
	clock_t end = clock();

	printf("%d blocks encrypted in %d/%d seconds.\n", ptSize >> 2, end-start, CLOCKS_PER_SEC);

	return 0;
}