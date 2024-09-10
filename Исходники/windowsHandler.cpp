void windowsHandler::generateRandomBytes(unsigned char* buffer, const unsigned int count)
{
	HCRYPTPROV cryptProvider = 0;
	CryptAcquireContext(&cryptProvider, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(cryptProvider, static_cast <unsigned long>(count), static_cast <unsigned char*>(buffer));
	CryptReleaseContext(cryptProvider, 0);
}