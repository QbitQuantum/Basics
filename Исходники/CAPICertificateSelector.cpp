std::string selectCAPICertificate() {
	const char* certStoreName = "MY";

	DWORD storeFlags = CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG | CERT_SYSTEM_STORE_CURRENT_USER;

	HCERTSTORE hstore = CertOpenStore(CERT_STORE_PROV_SYSTEM_A, 0, 0, storeFlags, certStoreName);
	if (!hstore) {
		return "";
	}

	HWND hwnd = GetForegroundWindow();
	if (!hwnd) {
		hwnd = GetActiveWindow();
	}

	std::string certificateDialogTitle = QT_TRANSLATE_NOOP("", "TLS Client Certificate Selection");
	std::string certificateDialogPrompt = QT_TRANSLATE_NOOP("", "Select a certificate to use for authentication");

	int titleLength = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, certificateDialogTitle.c_str(), -1, NULL, 0);
	int promptLength = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, certificateDialogPrompt.c_str(), -1, NULL, 0);

	wchar_t* titleChars = new wchar_t[titleLength];
	wchar_t* promptChars = new wchar_t[promptLength];

	//titleChars[titleLength] = '\0';
	//promptChars[promptLength] = '\0';

	titleLength = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, certificateDialogTitle.c_str(), -1, titleChars, titleLength);
	promptLength = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, certificateDialogPrompt.c_str(), -1, promptChars, promptLength);

	if (titleLength == 0 || promptLength == 0) {
		int error = GetLastError();
		switch (error) {
			case ERROR_INSUFFICIENT_BUFFER: SWIFT_LOG(error) << "Insufficient buffer for rendering cert dialog" << std::endl;break;
			case ERROR_INVALID_FLAGS: SWIFT_LOG(error) << "Invalid flags for rendering cert dialog" << std::endl;break;
			case ERROR_INVALID_PARAMETER: SWIFT_LOG(error) << "Invalid parameter for rendering cert dialog" << std::endl;break;
			case ERROR_NO_UNICODE_TRANSLATION: SWIFT_LOG(error) << "Invalid unicode for rendering cert dialog" << std::endl;break;
			default: SWIFT_LOG(error) << "Unexpected multibyte conversion errorcode" << std::endl;

		}
	}

	

	/* Call Windows dialog to select a suitable certificate */
	PCCERT_CONTEXT cert = CryptUIDlgSelectCertificateFromStore(hstore, hwnd, titleChars, promptChars, exclude_columns, 0, NULL);

	delete[] titleChars;
	delete[] promptChars;

	if (hstore) {
		CertCloseStore(hstore, 0);
	}

	std::string result;

	if (cert) {
		result = getCertUri(cert, certStoreName);
		CertFreeCertificateContext(cert);
	}

	return result;
}