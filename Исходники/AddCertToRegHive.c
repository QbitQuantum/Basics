int _tmain(int argc, _TCHAR* argv[]) {
	LONG retval;
	Params p;
	LPVOID cert, crl;
	DWORD certSz = 0, crlSz = 0, index = 0, disp = 0;
	HKEY rootKey = NULL, storesKey = NULL, key = NULL;

	HCERTSTORE hCertStore = NULL;
	TCHAR root[MAX_REG_KEY_LEN];

	// Get params
	if (!GetParams(&p, argc, argv)) {
		_tprintf(TEXT("Usage:\n"));
		_tprintf(TEXT("%s hive crt.cer [/CRL crl.crl] [/Store store]\n\n"), argv[0]);
		_tprintf(TEXT("hive\ta registry hive for HKLM\\SOFTWARE (user hives not supported)\n"));
		_tprintf(TEXT("  found at Windows\\System32\\config\\SOFTWARE (cannot use be an in-use hive)\n"));
		_tprintf(TEXT("crt.cer\tthe certificate to import\n"));
		_tprintf(TEXT("crl.crl\tif provided adds a CRL as well\n"));
		_tprintf(TEXT("store\tthe store to import to, defaults to ROOT\n\n"));
		return -1;
	}

	// Enable privileges
	if (!EnablePriv(SE_TAKE_OWNERSHIP_NAME) || !EnablePriv(SE_BACKUP_NAME) || !EnablePriv(SE_RESTORE_NAME)) {
		return LastError(TEXT("Failed to enable take ownership, backup, and restore privileges"), NULL);
	}

	// Read the certificate file
	if ((cert = Read(p.cert, &certSz)) == NULL) {
		return LastError(TEXT("Failed to read certificate file '%s'"), p.cert);
	}

	// Read the CRL file
	if (p.crl && ((crl = Read(p.crl, &crlSz)) == NULL)) {
		LocalFree(cert);
		return LastError(TEXT("Failed to read the CRL file '%s'"), p.crl);
	}

	// Find a subkey that's available
	_tcsncpy(root, TEXT("TEMPHIVE"), MAX_REG_KEY_LEN);
	if ((retval = RegOpenKeyEx(HKEY_LOCAL_MACHINE, root, 0, KEY_READ, &key)) != ERROR_FILE_NOT_FOUND) {
		if (retval != ERROR_SUCCESS) {
			LocalFree(crl);
			LocalFree(cert);
			return Error(TEXT("Failed to find subkey to load hive"), NULL, retval);
		}
		RegCloseKey(key);
		_sntprintf(root, MAX_REG_KEY_LEN, TEXT("TEMPHIVE%u"), index++);
	}
	key = NULL;

	// Load the hive
	if ((retval = RegLoadKey(HKEY_LOCAL_MACHINE, root, p.hive)) != ERROR_SUCCESS) {
		LocalFree(cert);
		if (crl) LocalFree(crl);
		return Error(TEXT("Failed to load hive file '%s'"), p.hive, retval);
	}

	// Open the HKLM\TEMPHIVE\Microsoft\SystemCertificates
	if ((retval = RegOpenKeyEx(HKEY_LOCAL_MACHINE, root, 0, KEY_ALL_ACCESS, &rootKey)) != ERROR_SUCCESS) {
		Error(TEXT("Failed to get root key '%s'"), root, retval);
	} else if ((retval = RegOpenKeyEx(rootKey, TEXT("Microsoft\\SystemCertificates"), 0, KEY_ALL_ACCESS, &storesKey)) != ERROR_SUCCESS) {
		Error(TEXT("Failed to get stores key: %u\n"), NULL, retval);

	// Create/Open the registry certificate store
	} else if ((retval = RegCreateKeyEx(storesKey, p.store, 0, NULL, REG_OPTION_BACKUP_RESTORE, KEY_ALL_ACCESS, NULL, &key, &disp)) != ERROR_SUCCESS) {
		Error(TEXT("Failed to create store key '%s'"), p.store, retval);

	// Open the store
	} else if ((hCertStore = CertOpenStore(CERT_STORE_PROV_REG, 0, (HCRYPTPROV)NULL, CERT_STORE_BACKUP_RESTORE_FLAG | CERT_STORE_OPEN_EXISTING_FLAG, key)) == NULL) {
		retval = LastError(TEXT("Failed to create certificate store"), NULL);

	// Add the certificate to the store
	} else if (!CertAddEncodedCertificateToStore(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, cert, certSz, CERT_STORE_ADD_REPLACE_EXISTING, NULL)) {
		retval = LastError(TEXT("Failed add certificate to store"), NULL);

	// Add the crl to the store
	} else if (crl && !CertAddEncodedCRLToStore(hCertStore, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, crl, crlSz, CERT_STORE_ADD_REPLACE_EXISTING, NULL)) {
		retval = LastError(TEXT("Failed add the CRL to store"), NULL);
	}

	// Cleanup
	if (hCertStore) { CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG); }
	if (key)		{ RegCloseKey(key); }
	if (storesKey)	{ RegCloseKey(storesKey); }
	if (rootKey)	{ RegCloseKey(rootKey); }
	LocalFree(crl);
	LocalFree(cert);

	// Unload the hive
	if ((disp = RegUnLoadKey(HKEY_LOCAL_MACHINE, root)) != ERROR_SUCCESS) {
		if (retval == ERROR_SUCCESS) { retval = disp; }
		Error(TEXT("Failed to unload the hive"), NULL, disp);
	}

	// Successful? Yeah!
	if (retval == ERROR_SUCCESS) {
		if (p.crl) {
			_tprintf(TEXT("Successfully added %s and %s to the %s store in %s\n\n"), p.cert, p.crl, p.store, p.hive);
		} else {
			_tprintf(TEXT("Successfully added %s to the %s store in %s\n\n"), p.cert, p.store, p.hive);
		}
	}

	return retval;
}