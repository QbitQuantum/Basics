void test_InitializeSecurityContext(void)
{
	uint32 cbMaxLen;
	uint32 fContextReq;
	void* output_buffer;
	CtxtHandle context;
	uint32 pfContextAttr;
	SECURITY_STATUS status;
	CredHandle credentials;
	TimeStamp expiration;
	SecPkgInfo* pPackageInfo;
	SEC_WINNT_AUTH_IDENTITY identity;
	SecurityFunctionTable* table;
	SecBuffer* p_SecBuffer;
	SecBuffer output_SecBuffer;
	SecBufferDesc output_SecBuffer_desc;

	table = InitSecurityInterface();

	status = QuerySecurityPackageInfo(NTLM_PACKAGE_NAME, &pPackageInfo);

	if (status != SEC_E_OK)
	{
		printf("QuerySecurityPackageInfo status: 0x%08X\n", status);
		return;
	}

	cbMaxLen = pPackageInfo->cbMaxToken;

	identity.User = (uint16*) xstrdup(test_User);
	identity.UserLength = sizeof(test_User);
	identity.Domain = (uint16*) xstrdup(test_Domain);
	identity.DomainLength = sizeof(test_Domain);
	identity.Password = (uint16*) xstrdup(test_Password);
	identity.PasswordLength = sizeof(test_Password);
	identity.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;

	status = table->AcquireCredentialsHandle(NULL, NTLM_PACKAGE_NAME,
			SECPKG_CRED_OUTBOUND, NULL, &identity, NULL, NULL, &credentials, &expiration);

	if (status != SEC_E_OK)
	{
		printf("AcquireCredentialsHandle status: 0x%08X\n", status);
		return;
	}

	fContextReq = ISC_REQ_REPLAY_DETECT | ISC_REQ_SEQUENCE_DETECT | ISC_REQ_CONFIDENTIALITY | ISC_REQ_DELEGATE;

	output_buffer = xmalloc(cbMaxLen);

	output_SecBuffer_desc.ulVersion = 0;
	output_SecBuffer_desc.cBuffers = 1;
	output_SecBuffer_desc.pBuffers = &output_SecBuffer;

	output_SecBuffer.cbBuffer = cbMaxLen;
	output_SecBuffer.BufferType = SECBUFFER_TOKEN;
	output_SecBuffer.pvBuffer = output_buffer;

	status = table->InitializeSecurityContext(&credentials, NULL, NULL, fContextReq, 0, 0, NULL, 0,
			&context, &output_SecBuffer_desc, &pfContextAttr, &expiration);

	if (status != SEC_I_CONTINUE_NEEDED)
	{
		printf("InitializeSecurityContext status: 0x%08X\n", status);
		return;
	}

	printf("cBuffers: %d ulVersion: %d\n", output_SecBuffer_desc.cBuffers, output_SecBuffer_desc.ulVersion);

	p_SecBuffer = &output_SecBuffer_desc.pBuffers[0];

	printf("BufferType: 0x%04X cbBuffer:%d\n", p_SecBuffer->BufferType, p_SecBuffer->cbBuffer);

	freerdp_hexdump((uint8*) p_SecBuffer->pvBuffer, p_SecBuffer->cbBuffer);

	table->FreeCredentialsHandle(&credentials);

	FreeContextBuffer(pPackageInfo);
}