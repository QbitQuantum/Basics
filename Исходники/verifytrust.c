static BOOL iResolveAPI2(tVerifyTrustData* d)
{
	d->m_hWintrustDll = LoadLibraryA("WINTRUST");
	if (!d->m_hWintrustDll)
		return FALSE;
	d->m_hCrypt32Dll = LoadLibraryA("CRYPT32");
	if (!d->m_hCrypt32Dll)
		return FALSE;
	
	memset(&d->vi, 0, sizeof(OSVERSIONINFOA));
	d->vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	if ( !GetVersionExA(&d->vi) )
		return FALSE;

	_RESOLVE_API(d->m_hWintrustDll, WinVerifyTrust);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATAdminAcquireContext);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATAdminCalcHashFromFileHandle);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATAdminEnumCatalogFromHash);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATCatalogInfoFromContext);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATAdminReleaseCatalogContext);
	_RESOLVE_API(d->m_hWintrustDll, CryptCATAdminReleaseContext);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertOpenStore);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertEnumCertificatesInStore);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertGetCertificateChain);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertFindChainInStore);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertVerifyCertificateChainPolicy);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertFreeCertificateChainEngine);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertFreeCertificateChain);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertFreeCertificateContext);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertCloseStore);
	_RESOLVE_API(d->m_hCrypt32Dll,  CertGetNameStringA);
	return TRUE;
}