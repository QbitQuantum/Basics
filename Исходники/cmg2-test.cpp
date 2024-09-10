BYTE* DecryptAndVerify(
	BYTE  *pbSignedAndEncryptedBlob,
	DWORD  cbSignedAndEncryptedBlob)
{
	//---------------------------------------------------------------
	// Declare and initialize local variables.

	HCERTSTORE hCertStore;
	CRYPT_DECRYPT_MESSAGE_PARA DecryptPara;
	CRYPT_VERIFY_MESSAGE_PARA VerifyPara;
	DWORD dwSignerIndex = 0;
	BYTE *pbDecrypted;
	DWORD cbDecrypted;

	//---------------------------------------------------------------
	// Open the certificate store.

	if ( !( hCertStore = CertOpenStore(
		CERT_STORE_PROV_SYSTEM,
		0,
		NULL,
		CERT_SYSTEM_STORE_CURRENT_USER,
		L"my")))
	{
		MyHandleError(TEXT("The MY store could not be opened."));
	}

	//---------------------------------------------------------------
	// Initialize the needed data structures.

	DecryptPara.cbSize = sizeof(CRYPT_DECRYPT_MESSAGE_PARA);
	DecryptPara.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
	DecryptPara.cCertStore = 1;
	DecryptPara.rghCertStore = &hCertStore;

	VerifyPara.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);
	VerifyPara.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
	VerifyPara.hCryptProv = 0;
	VerifyPara.pfnGetSignerCertificate = NULL;
	VerifyPara.pvGetArg = NULL;
	pbDecrypted = NULL;
	cbDecrypted = 0;

	//---------------------------------------------------------------
	// Call CryptDecryptAndVerifyMessageSignature a first time
	// to determine the needed size of the buffer to hold the 
	// decrypted message.

	if(!(CryptDecryptAndVerifyMessageSignature(
		&DecryptPara,
		&VerifyPara,
		dwSignerIndex,
		pbSignedAndEncryptedBlob,
		cbSignedAndEncryptedBlob,
		NULL,           // pbDecrypted
		&cbDecrypted,
		NULL,
		NULL)))
	{
		DWORD const errcode = GetLastError();
		std::wcerr << format_sys_message<TCHAR>(errcode) << TEXT("\n"); 

		MyHandleError(TEXT("Failed getting size."));
	}

	//---------------------------------------------------------------
	// Allocate memory for the buffer to hold the decrypted
	// message.

	if(!(pbDecrypted = (BYTE *)malloc(cbDecrypted)))
	{
		MyHandleError(TEXT("Memory allocation failed."));
	}

	if(!(CryptDecryptAndVerifyMessageSignature(
		&DecryptPara,
		&VerifyPara,
		dwSignerIndex,
		pbSignedAndEncryptedBlob,
		cbSignedAndEncryptedBlob,
		pbDecrypted,
		&cbDecrypted,
		NULL,
		NULL)))
	{
		pbDecrypted = NULL;
	}

	//---------------------------------------------------------------
	// Close the certificate store.

	CertCloseStore(
		hCertStore,
		0);

	//---------------------------------------------------------------
	// Return the decrypted string or NULL.

	return pbDecrypted;

} // End of DecryptandVerify.