extern "C" HRESULT DAPI CertInstallSingleCertificate(
    __in HCERTSTORE hStore,
    __in PCCERT_CONTEXT pCertContext,
    __in LPCWSTR wzName
    )
{
    HRESULT hr = S_OK;
    CERT_BLOB blob = { };

    DWORD dwKeySpec = 0;

    HCRYPTPROV hCsp = NULL;
    LPWSTR pwszTmpContainer = NULL;
    LPWSTR pwszProviderName = NULL;
    DWORD dwProviderType = 0;
    BOOL fAcquired = TRUE;

    SECURITY_DESCRIPTOR* pSecurity = NULL;
    SECURITY_DESCRIPTOR* pSecurityNew = NULL;

    // Update the friendly name of the certificate to be configured.
    blob.pbData = (BYTE*)wzName;
    blob.cbData = (lstrlenW(wzName) + 1) * sizeof(WCHAR); // including terminating null

    if (!::CertSetCertificateContextProperty(pCertContext, CERT_FRIENDLY_NAME_PROP_ID, 0, &blob))
    {
        ExitWithLastError(hr, "Failed to set the friendly name of the certificate: %ls", wzName);
    }

    if (!::CertAddCertificateContextToStore(hStore, pCertContext, CERT_STORE_ADD_REPLACE_EXISTING, NULL))
    {
        ExitWithLastError(hr, "Failed to add certificate to the store.");
    }

    // if the certificate has a private key, grant Administrators access
    if (CertHasPrivateKey(pCertContext, &dwKeySpec))
    {
        if (AT_KEYEXCHANGE == dwKeySpec || AT_SIGNATURE == dwKeySpec)
        {
            // We added a CSP key
            hr = GetCryptProvFromCert(NULL, pCertContext, &hCsp, &dwKeySpec, &fAcquired, &pwszTmpContainer, &pwszProviderName, &dwProviderType);
            ExitOnFailure(hr, "Failed to get handle to CSP");

            hr = GetProvSecurityDesc(hCsp, &pSecurity);
            ExitOnFailure(hr, "Failed to get security descriptor of CSP");

            hr = AclAddAdminToSecurityDescriptor(pSecurity, &pSecurityNew);
            ExitOnFailure(hr, "Failed to create new security descriptor");

            hr = SetProvSecurityDesc(hCsp, pSecurityNew);
            ExitOnFailure(hr, "Failed to set Admin ACL on CSP");
        }

        if (CERT_NCRYPT_KEY_SPEC == dwKeySpec)
        {
            // We added a CNG key
            // TODO change ACL on CNG key
        }
    }
LExit:
    if (hCsp)
    {
        FreeCryptProvFromCert(fAcquired, hCsp, NULL, dwProviderType, NULL);
    }

    ReleaseMem(pSecurity);

    if (pSecurityNew)
    {
        AclFreeSecurityDescriptor(pSecurityNew);
    }
    return hr;
}