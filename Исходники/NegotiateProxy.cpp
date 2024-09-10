SECURITY_STATUS getToken(char **negotiateToken, WCHAR *targetName, WCHAR *hostName)
{
	//----------------------------------------------------------------------
	unsigned long cPackages;
	PSecPkgInfo PackageInfo;
	SECURITY_STATUS stat;

	// Get the name of the package
	stat = EnumerateSecurityPackages(
		&cPackages,
		&PackageInfo);

	if (stat != SEC_E_OK)
	{
		wprintf(
			L"Security function failed with error: %i\n",
			stat);
		return stat;
	}

	SEC_WCHAR *szPackage = PackageInfo->Name;
	unsigned long m_cbMaxToken = PackageInfo->cbMaxToken;

	PBYTE m_pOutBuf = (PBYTE)malloc(m_cbMaxToken);

	//--------------------------------------------------------------------

	CredHandle hCredential;
	TimeStamp tsExpiry;
	PSEC_WINNT_AUTH_IDENTITY_OPAQUE pAuthIdentity = NULL; // The structure for storing user data entered

	stat = AcquireCredentialsHandle(
		NULL,
		szPackage,
		SECPKG_CRED_OUTBOUND,
		NULL,
		pAuthIdentity,
		NULL,
		NULL,
		&hCredential,
		&tsExpiry);

	if (stat != SEC_E_OK)
	{
		wprintf(
			L"Credentials function failed with error: %i\n",
			stat);
		return stat;
	}

	//--------------------------------------------------------------------

	CtxtHandle		m_hCtxt;
	SecBufferDesc	outSecBufDesc;
	SecBuffer		outSecBuf;

	unsigned long	fContextAttr;


	// prepare output buffer
	outSecBufDesc.ulVersion = 0;
	outSecBufDesc.cBuffers = 1;
	outSecBufDesc.pBuffers = &outSecBuf;
	outSecBuf.cbBuffer = m_cbMaxToken;
	outSecBuf.BufferType = SECBUFFER_TOKEN;
	outSecBuf.pvBuffer = m_pOutBuf;

	stat = InitializeSecurityContext(
		&hCredential,
		NULL,
		targetName,
		ISC_REQ_CONFIDENTIALITY,
		0,	// reserved1
		SECURITY_NATIVE_DREP,
		NULL,
		0,	// reserved2
		&m_hCtxt,
		&outSecBufDesc,
		&fContextAttr,
		&tsExpiry);

	FreeCredentialsHandle(&hCredential);

	switch (stat)
	{
	case SEC_I_CONTINUE_NEEDED: 
	case SEC_I_COMPLETE_AND_CONTINUE: CompleteAuthToken(&m_hCtxt, &outSecBufDesc); break;
	case SEC_E_OK: break;
	default: return stat;
	}

	DeleteSecurityContext(&m_hCtxt);
	FreeContextBuffer(PackageInfo);

	if (outSecBuf.cbBuffer)
	{
		base64_encode(reinterpret_cast < char* > (m_pOutBuf), outSecBuf.cbBuffer, negotiateToken);
	}
	else
	{
		return -1;
	}

	if (strlen(*negotiateToken) < 500)
	{
		CREDUI_INFO creduiInfo = { 0 };
		creduiInfo.cbSize = sizeof(creduiInfo);
		// Change the message text and caption to the actual text for your dialog.
		SEC_WCHAR message[NI_MAXHOST];

		_snwprintf_s(
			message,
			NI_MAXHOST,
			_TRUNCATE,
			L"Enter your username and password to connect to %s",
			hostName);

		creduiInfo.pszCaptionText = L"Connect to the proxy-server";
		creduiInfo.pszMessageText = message;

		BOOL fSave = TRUE; // Checkmark "Remember user"

		
		stat = SspiPromptForCredentials(
			targetName,
			&creduiInfo,
			0,
			szPackage,
			NULL,
			&pAuthIdentity,
			&fSave,
			0);
	}

	return SEC_E_OK;
}