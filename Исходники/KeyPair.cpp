void CKeyPair::LoadFromFile(PCHAR szFileName) 
{

	DWORD dwKeySize;
	BYTE *pbKeyBlob;
	FILE *fiKey;

	// Load the private key from a file
	fopen_s(&fiKey, (CHAR*)szFileName, "rb");
	fread(&dwKeySize, sizeof(dwKeySize), 1, fiKey);
	pbKeyBlob = new BYTE[dwKeySize];
	fread(pbKeyBlob, 1, dwKeySize, fiKey);
	fclose(fiKey);

	// Load the key pair
	HCRYPTPROV hCryptProv = m_pContext->GetProvider();
	CryptImportKey(hCryptProv, pbKeyBlob, dwKeySize, NULL, CRYPT_EXPORTABLE, &m_hCryptKey);

	// Clean up memory
	delete[] pbKeyBlob;

}