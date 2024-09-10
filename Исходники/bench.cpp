void BenchMarkEncryption(const char *name, PK_Encryptor &key, double timeTotal, bool pc=false)
{
	unsigned int len = 16;
	LC_RNG rng(time(NULL));
	SecByteBlock plaintext(len), ciphertext(key.CipherTextLength(len));
	rng.GetBlock(plaintext, len);

	clock_t start = clock();
	unsigned int i;
	double timeTaken;
	for (timeTaken=(double)0, i=0; timeTaken < timeTotal; timeTaken = double(clock() - start) / CLOCK_TICKS_PER_SECOND, i++)
		key.Encrypt(rng, plaintext, len, ciphertext);

	OutputResultOperations(name, "Encryption", pc, i, timeTaken);
}