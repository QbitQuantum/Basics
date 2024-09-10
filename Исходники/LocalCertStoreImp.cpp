HRESULT CLocalCertStoreImp::AddCertificate(CCertificate &certificate)
{
    HRESULT hr = S_OK;
    DWORD nCertEncodedSize = 0;

    // cert store must be opened first...
    if (m_hCertStoreHandle == NULL)
    {
        return E_UNEXPECTED;
    }

    if (CertAddEncodedCertificateToStore(
        m_hCertStoreHandle, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
        certificate.get_EncodedData(nCertEncodedSize), nCertEncodedSize,
        CERT_STORE_ADD_NEW, NULL) == FALSE)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }
    
    return hr;
}