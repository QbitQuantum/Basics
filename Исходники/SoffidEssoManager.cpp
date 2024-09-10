// Read URL server
LPSTR SoffidEssoManager::readURL (HINTERNET hSession, const wchar_t* host, int port,
		LPCWSTR path, BOOL allowUnknownCA, size_t *pSize)
{
	BOOL bResults = FALSE;
	HINTERNET hConnect = NULL, hRequest = NULL;

	DWORD dwDownloaded = -1;
	BYTE *buffer = NULL;

	if (debug)
	{
		log("Connecting to %s:%d...\n", host, port);
	}

	hConnect = WinHttpConnect(hSession, host, port, 0);

	if (hConnect)
	{
		if (debug)
		{
			log("Performing request %s...\n", path);
		}

		hRequest = WinHttpOpenRequest(hConnect, L"GET", path, NULL, WINHTTP_NO_REFERER,
				WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
	}

	// Send a request.
	if (hRequest)
	{
		if (debug)
			log("Sending request ...\n");

		WinHttpSetOption(hRequest, WINHTTP_OPTION_CLIENT_CERT_CONTEXT, NULL, 0);

		if (allowUnknownCA)
		{
			DWORD flags = SECURITY_FLAG_IGNORE_UNKNOWN_CA;
			WinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, (LPVOID) &flags,
					sizeof flags);
		}

		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
				WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
	}

	if (bResults && allowUnknownCA)
	{
		// Agreagar la CA ROOT
		PCERT_CONTEXT context;
		DWORD dwSize = sizeof context;
		BOOL result = WinHttpQueryOption(hRequest, WINHTTP_OPTION_SERVER_CERT_CONTEXT,
				&context, &dwSize);

		if (!result)
		{
			log("Cannot get context\n");
//			notifyError();
		}

		PCCERT_CONTEXT issuerContext = CertFindCertificateInStore(context->hCertStore,
				X509_ASN_ENCODING, 0, CERT_FIND_ISSUER_OF, context, NULL);
		HCERTSTORE systemStore = CertOpenStore((LPCSTR) 13, // CERT_STORE_PROV_SYSTEM_REGISTRY_W
				0, (HCRYPTPROV) NULL, (2 << 16) | // CERT_SYSTEM_STORE_LOCAL_MACHINE
						0x1000, // CERT_STORE_MAXIMUM_ALLOWED
				L"ROOT");
		CertAddCertificateContextToStore(systemStore, issuerContext,
				1 /*CERT_STORE_ADD_NEW*/, NULL);

		CertFreeCertificateContext(issuerContext);
		CertFreeCertificateContext(context);
	}

	// End the request.
	if (bResults)
	{
		if (debug)
			log("Waiting for response....\n");

		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	// Keep checking for data until there is nothing left.
	DWORD used = 0;
	if (bResults)
	{
		const DWORD chunk = 4096;
		DWORD allocated = 0;
		do
		{
			if (used + chunk > allocated)
			{
				allocated += chunk;
				buffer = (LPBYTE) realloc(buffer, allocated);
			}

			dwDownloaded = 0;
			if (!WinHttpReadData(hRequest, &buffer[used], chunk, &dwDownloaded))
				dwDownloaded = -1;

			else
				used += dwDownloaded;
		} while (dwDownloaded > 0);

		buffer[used] = '\0';
	}

	DWORD dw = GetLastError();
	if (!bResults && debug)
	{
		if (dw == ERROR_WINHTTP_CANNOT_CONNECT)
			log("Error: Cannot connect\n");
		else if (dw == ERROR_WINHTTP_CLIENT_AUTH_CERT_NEEDED)
			log("Error: Client CERT required\n");
		else if (dw == ERROR_WINHTTP_CONNECTION_ERROR)
			log("Error: Connection error\n");
		else if (dw == ERROR_WINHTTP_INCORRECT_HANDLE_STATE)
			log("Error: ERROR_WINHTTP_INCORRECT_HANDLE_STATE\n");
		else if (dw == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE)
			log("Error: ERROR_WINHTTP_INCORRECT_HANDLE_TYPE\n");
		else if (dw == ERROR_WINHTTP_INTERNAL_ERROR)
			log("Error: ERROR_WINHTTP_INTERNAL_ERROR\n");
		else if (dw == ERROR_WINHTTP_INVALID_URL)
			log("Error: ERROR_WINHTTP_INVALID_URL\n");
		else if (dw == ERROR_WINHTTP_LOGIN_FAILURE)
			log("Error: ERROR_WINHTTP_LOGIN_FAILURE\n");
		else if (dw == ERROR_WINHTTP_NAME_NOT_RESOLVED)
			log("Error: ERROR_WINHTTP_NAME_NOT_RESOLVED\n");
		else if (dw == ERROR_WINHTTP_OPERATION_CANCELLED)
			log("Error: ERROR_WINHTTP_OPERATION_CANCELLED\n");
		else if (dw == ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW)
			log("Error: ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW\n");
		else if (dw == ERROR_WINHTTP_SECURE_FAILURE)
			log("Error: ERROR_WINHTTP_SECURE_FAILURE\n");
		else if (dw == ERROR_WINHTTP_SHUTDOWN)
			log("Error: ERROR_WINHTTP_SHUTDOWN\n");
		else if (dw == ERROR_WINHTTP_TIMEOUT)
			log("Error: ERROR_WINHTTP_TIMEOUT\n");
		else if (dw == ERROR_WINHTTP_UNRECOGNIZED_SCHEME)
			log("Error: ERROR_WINHTTP_UNRECOGNIZED_SCHEME\n");
		else if (dw == ERROR_NOT_ENOUGH_MEMORY)
			log("Error: ERROR_NOT_ENOUGH_MEMORY\n");
		else if (dw == ERROR_INVALID_PARAMETER)
			log("Error: ERROR_INVALID_PARAMETER\n");
		else if (dw == ERROR_WINHTTP_RESEND_REQUEST)
			log("Error:  ERROR_WINHTTP_RESEND_REQUEST\n");
		else if (dw != ERROR_SUCCESS)
		{
			log("Unkonwn error %d\n", dw);
		}
//		notifyError();
	}

	// Close any open handles.
	if (hRequest)
		WinHttpCloseHandle(hRequest);
	if (hConnect)
		WinHttpCloseHandle(hConnect);
	if (hSession)
		WinHttpCloseHandle(hSession);

	SetLastError(dw);

	if (pSize != NULL)
		*pSize = used;

	return (LPSTR) buffer;
}