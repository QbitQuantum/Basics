void BenchMarkDecryption(const char *name, PK_Decryptor &priv, PK_Encryptor &pub, double timeTotal)
{
	unsigned int len = 16;
	SecByteBlock ciphertext(pub.CiphertextLength(len));
	SecByteBlock plaintext(pub.MaxPlaintextLength(ciphertext.size()));
	GlobalRNG().GenerateBlock(plaintext, len);
	pub.Encrypt(GlobalRNG(), plaintext, len, ciphertext);

	const clock_t start = clock();
	unsigned int i;
	double timeTaken;
	for (timeTaken=(double)0, i=0; timeTaken < timeTotal; timeTaken = double(clock() - start) / CLOCK_TICKS_PER_SECOND, i++)
		priv.Decrypt(GlobalRNG(), ciphertext, ciphertext.size(), plaintext);

	OutputResultOperations(name, "Decryption", false, i, timeTaken);
}