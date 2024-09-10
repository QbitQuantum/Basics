char* CompleteGssapi(HANDLE hSecurity, unsigned char *szChallenge, unsigned chlsz)
{
	if (!szChallenge || !szChallenge[0]) return NULL;

	NtlmHandleType* hNtlm = (NtlmHandleType*)hSecurity;
	unsigned char inDataBuffer[1024];

	SecBuffer inBuffers[2] = 
	{
		{ sizeof(inDataBuffer), SECBUFFER_DATA, inDataBuffer },
		{ chlsz, SECBUFFER_STREAM, szChallenge },
	};

	SecBufferDesc inBuffersDesc = { SECBUFFER_VERSION, 2, inBuffers };

	unsigned long qop = 0;
	SECURITY_STATUS sc = g_pSSPI->DecryptMessage(&hNtlm->hClientContext, &inBuffersDesc, 0, &qop);
	if (sc != SEC_E_OK) 
	{
		ReportSecError(sc, __LINE__);
		return NULL;
	}

	unsigned char LayerMask = inDataBuffer[0];
	unsigned int MaxMessageSize = htonl(*(unsigned*)&inDataBuffer[1]);

	SecPkgContext_Sizes sizes;
	sc = g_pSSPI->QueryContextAttributes(&hNtlm->hClientContext, SECPKG_ATTR_SIZES, &sizes);
	if (sc != SEC_E_OK) 
	{
		ReportSecError(sc, __LINE__);
		return NULL;
	}

	unsigned char *tokenBuffer = (unsigned char*)alloca(sizes.cbSecurityTrailer);
	unsigned char *paddingBuffer = (unsigned char*)alloca(sizes.cbBlockSize);

	unsigned char outDataBuffer[4] = { 1, 0, 16, 0 };

	SecBuffer outBuffers[3] = 
	{
		{ sizes.cbSecurityTrailer, SECBUFFER_TOKEN, tokenBuffer },
		{ sizeof(outDataBuffer), SECBUFFER_DATA, outDataBuffer },
		{ sizes.cbBlockSize, SECBUFFER_PADDING, paddingBuffer }
	};
	SecBufferDesc outBuffersDesc = { SECBUFFER_VERSION, 3, outBuffers };

	sc = g_pSSPI->EncryptMessage(&hNtlm->hClientContext, SECQOP_WRAP_NO_ENCRYPT, &outBuffersDesc, 0);
	if (sc != SEC_E_OK) 
	{
		ReportSecError(sc, __LINE__);
		return NULL;
	}

	unsigned i, ressz = 0;
	for (i = 0; i < outBuffersDesc.cBuffers; i++) 
		ressz += outBuffersDesc.pBuffers[i].cbBuffer;


	unsigned char *response = (unsigned char*)alloca(ressz), *p = response;
	for (i = 0; i < outBuffersDesc.cBuffers; i++) 
	{
		memcpy(p, outBuffersDesc.pBuffers[i].pvBuffer, outBuffersDesc.pBuffers[i].cbBuffer);
		p += outBuffersDesc.pBuffers[i].cbBuffer;
	}

	NETLIBBASE64 nlb64;
	nlb64.cbDecoded = ressz;
	nlb64.pbDecoded = response;
	nlb64.cchEncoded = Netlib_GetBase64EncodedBufferSize(nlb64.cbDecoded);
	nlb64.pszEncoded = (char*)alloca(nlb64.cchEncoded);
	if (!NetlibBase64Encode(0,(LPARAM)&nlb64)) return NULL;

	return mir_strdup(nlb64.pszEncoded);
} 