int _tmain(int argc, _TCHAR* argv[])
{
	//--------------------------------------------------------------------
	// Declare and initialize variables.
	HCERTSTORE       hCertStore = NULL;        
	PCCERT_CONTEXT   pCertContext = NULL;      
	TCHAR * pszStoreName = TEXT("MY");
	HCRYPTKEY hKey = NULL;
	HCRYPTPROV hProv = NULL;
	DWORD dwKeySpec = 0;
	BOOL bCallerFreeProv = FALSE;
	HCRYPTHASH hHash;
	DWORD dwSigLen= 0;
	BYTE * pbSignature = NULL;

	//-------------------------------------------------------------
	// Declare and initialize variables.
	BYTE *pbBuffer= (BYTE *)"The data that is to be hashed and signed.";
	DWORD dwBufferLen = strlen((char *)pbBuffer)+1;

	//--------------------------------------------------------------------
	//   Open a certificate store.
	if ( hCertStore = CertOpenSystemStore(
		NULL,
		pszStoreName))
	{
		fprintf(stderr,"The store has been opened.\n");
	}
	else
	{
		printf("Unable to open store.\n");
		goto err;
	}
	//--------------------------------------------------------------------
	//  Display a list of the certificates in the store and 
	//  allow the user to select a certificate. 
	if(!(pCertContext = CryptUIDlgSelectCertificateFromStore(
		hCertStore,      // Open the store that contains the certificates to
		// display
		NULL,
		NULL,
		NULL,
		CRYPTUI_SELECT_LOCATION_COLUMN,
		0,
		NULL)))
	{
		printf("Select Certificate UI failed.\n" );
		goto err;
	}

#if 1
	//获取CSP句柄
	if (!CryptAcquireCertificatePrivateKey(pCertContext, 0, NULL, &hProv, &dwKeySpec, &bCallerFreeProv))
	{
		printf("CryptAcquireCertificatePrivateKey failed.\n" );
		goto err;
	}

	//获取密钥句柄
	if(!CryptGetUserKey(hProv, dwKeySpec, &hKey))
	{
		printf("CryptGetUserKey failed.\n" );
		goto err;
	}

	
	
	//--------------------------------------------------------------------
	// Acquire a hash object handle.
	if(CryptCreateHash(
		hProv, 
		CALG_MD5, 
		0, 
		0, 
		&hHash)) 
	{
		printf("An empty hash object has been created. \n");
	}
	else
	{
		printf("Error during CryptBeginHash!\n");
		goto err;
	}


	//--------------------------------------------------------------------
	//  This code assumes that the handle of a cryptographic context 
	//  has been acquired and that a hash object has been created 
	//  and its handle (hHash) is available.
	if(CryptHashData(
		hHash, 
		pbBuffer, 
		dwBufferLen, 
		0)) 
	{
		printf("The data buffer has been added to the hash.\n");
	}
	else
	{
		printf("Error during CryptHashData.\n");
		goto err;
	}


	//--------------------------------------------------------------------
	// Determine the size of the signature and allocate memory.
	dwSigLen= 0;
	if(CryptSignHash(
		hHash, 
		dwKeySpec, 
		NULL, 
		0, 
		NULL, 
		&dwSigLen)) 
	{
		printf("Signature length %d found.\n",dwSigLen);
	}
	else
	{
		printf("Error during CryptSignHash\n");
		goto err;
	}
	//--------------------------------------------------------------------
	// Allocate memory for the signature buffer.

	if(pbSignature = (BYTE *)malloc(dwSigLen))
	{
		printf("Memory allocated for the signature.\n");
	}
	else
	{
		printf("Out of memory\n");
		goto err;
	}
	//--------------------------------------------------------------------
	// Sign the hash object.

	if(CryptSignHash(
		hHash, 
		dwKeySpec, 
		NULL, 
		0, 
		pbSignature, 
		&dwSigLen)) 
	{
		printf("pbSignature is the hash signature.\n");
	}
	else
	{
		printf("Error during CryptSignHash.\n");
		goto err;
	}


	{
		DWORD dwBlobLen = 0;
		BYTE * pbKeyBlob = 0;
		HCRYPTKEY hPubKey = 0; 

		if(CryptExportKey(  
			hKey, 
			NULL, 
			PUBLICKEYBLOB,       //导出公钥
			0,   
			NULL,
			&dwBlobLen))         //返回密钥数据长度
		{
			printf("Size of the BLOB for the public key determined. \n");
		}
		else
		{
			printf("Error computing BLOB length.\n");
			goto err;
		}

		if(pbKeyBlob = (BYTE*)malloc(dwBlobLen))
		{
			printf("Memory has been allocated for the BLOB. \n");
		}
		else
		{
			printf("Out of memory. \n");
			goto err;
		}
		if(CryptExportKey(  
			hKey,
			NULL, 
			PUBLICKEYBLOB,   
			0,   
			pbKeyBlob,       //返回密钥数据
			&dwBlobLen)) //导出的密钥数据的长度
		{
			printf("Contents have been written to the BLOB. \n");
		}
		else
		{
			printf("Error exporting key.\n");
			goto err;
		}

		if(CryptImportKey(hProv,pbKeyBlob, dwBlobLen, NULL, 0, &hPubKey))
		{
			printf("CryptImportKey OK. \n");
		}
		else
		{
			printf("Error CryptImportKey.\n");
			goto err;
		}

		if(CryptVerifySignature(hHash, pbSignature, dwSigLen,hPubKey,NULL,0))
		{
			printf("verify OK.\n");
		}
		else
		{
			printf("Error during CryptVerifySignature.\n");
			goto err;
		}

	}

	if(CryptVerifySignature(hHash, pbSignature, dwSigLen,hKey,NULL,0))
	{
		printf("verify OK.\n");
	}
	else
	{
		printf("Error during CryptVerifySignature.\n");
		goto err;
	}

#endif

	BYTE* pbMessage =  

		(BYTE*)"CryptoAPI is a good way to handle security";  
	DWORD cbMessage = strlen((char*) pbMessage)+1;  
	//证书的上下文  

	CRYPT_SIGN_MESSAGE_PARA SigParams;  

	DWORD cbSignedMessageBlob;  

	BYTE *pbSignedMessageBlob;  

	DWORD cbDecodedMessageBlob;  

	BYTE *pbDecodedMessageBlob;  

	CRYPT_VERIFY_MESSAGE_PARA VerifyParams;  

	const BYTE* MessageArray[] = {pbMessage};  

	DWORD MessageSizeArray[1];  

	MessageSizeArray[0] = cbMessage;  

	printf("Begin processing. \n");  
	printf(" The message to be signed is\n-> %s.\n",pbMessage);  

	//--------------------------------------------------------------------  
	//初始化签名结构  
	SigParams.cbSize = sizeof(CRYPT_SIGN_MESSAGE_PARA);  

	SigParams.dwMsgEncodingType = (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING);  

	SigParams.pSigningCert = pCertContext;  

	SigParams.HashAlgorithm.pszObjId = szOID_RSA_MD5;  

	SigParams.HashAlgorithm.Parameters.cbData = NULL;  

	SigParams.cMsgCert = 1;  

	SigParams.rgpMsgCert = &pCertContext;  

	SigParams.cAuthAttr = 0;  

	SigParams.dwInnerContentType = 0;  

	SigParams.cMsgCrl = 0;  

	SigParams.cUnauthAttr = 0;  

	SigParams.dwFlags = 0;  

	SigParams.pvHashAuxInfo = NULL;  

	SigParams.rgAuthAttr = NULL;  

	//首先得到BLOB的大小  
	if(CryptSignMessage(  
		&SigParams, // Signature parameters  
		FALSE, // Not detached  
		1, // Number of messages  
		MessageArray, // Messages to be signed  
		MessageSizeArray, // Size of messages  
		NULL, // Buffer for signed message  
		&cbSignedMessageBlob)) // Size of buffer  
	{
		printf("The size of the BLOB is %d.\n",cbSignedMessageBlob);  
	} 
	else  
	{
		printf("Getting signed BLOB size failed");  
	}  

	//--------------------------------------------------------------------  
	//分配BLOB的内存.  

	if(!(pbSignedMessageBlob =  
		(BYTE*)malloc(cbSignedMessageBlob)))  
	{ 
		printf("Memory allocation error while signing.");  
	}  

	if(CryptSignMessage(  
		&SigParams, //  
		FALSE, //  
		1, //消息数量  
		MessageArray, //待签名的消息  
		MessageSizeArray, //消息大小  
		pbSignedMessageBlob, //缓冲区 
		&cbSignedMessageBlob)) //缓冲区大小  
	{  
		printf("The message was signed successfully. \n");  
	} 
	else  
	{  
		printf("Error getting signed BLOB");  
	}  

	//--------------------------------------------------------------------
	//验证签名信息  
	//--------------------------------------------------------------------
	//初始化VerifyParams结构.  

	VerifyParams.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);  

	VerifyParams.dwMsgAndCertEncodingType =  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING); 

	VerifyParams.hCryptProv = 0;  

	VerifyParams.pfnGetSignerCertificate = NULL;  

	VerifyParams.pvGetArg = NULL;  

	if(CryptVerifyMessageSignature(  
		&VerifyParams, //.  
		0, //  
		pbSignedMessageBlob, //.  
		cbSignedMessageBlob, //  
		NULL, //  
		&cbDecodedMessageBlob, //
		NULL)) // Pointer to signer certificate.  
	{  
		printf("%d bytes need for the buffer.\n",cbDecodedMessageBlob);  
	}  
	else  
	{  
		printf("Verification message failed. \n");  
	}  

	//为缓冲区分配内存.  
	if(!(pbDecodedMessageBlob =  
		(BYTE*)malloc(cbDecodedMessageBlob)))  
	{  
		printf("Memory allocation error allocating decode BLOB.");  
	}  

	//得到缓冲区的大小  
	if(CryptVerifyMessageSignature(  
		&VerifyParams, // Verify parameters.  
		0, // Signer index.  
		pbSignedMessageBlob, // Pointer to signed BLOB.  
		cbSignedMessageBlob, // Size of signed BLOB.  
		pbDecodedMessageBlob, // Buffer for decoded message.  
		&cbDecodedMessageBlob, // Size of buffer.  
		NULL)) // Pointer to signer certificate.  

	{  
		printf("The verified message is \n-> %s \n",pbDecodedMessageBlob);  
	}  
	else  
	{  
		printf("Verification message failed. \n"); 
	}  

err:
	WTF_PrintErrorMsg();

	if(pbSignedMessageBlob)  
	{
		free(pbSignedMessageBlob);  
	}

	if(pbDecodedMessageBlob)  
	{
		free(pbDecodedMessageBlob);  
	}

	if (pbSignature)
	{
		free(pbSignature);
	}

	if(hHash) 
	{
		CryptDestroyHash(hHash);
	}
	if (hKey)
	{
		CryptDestroyKey(hKey);
	}

	if (hProv)
	{
		CryptReleaseContext(hProv, 0);
	}
	if (pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
	}
	
	if (hCertStore)
	{
		CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
	}
	
	return 0;
}