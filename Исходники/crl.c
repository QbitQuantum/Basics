PCCRL_CONTEXT WINAPI CertCreateCRLContext(DWORD dwCertEncodingType,
 const BYTE* pbCrlEncoded, DWORD cbCrlEncoded)
{
    PCRL_CONTEXT crl = NULL;
    BOOL ret;
    PCRL_INFO crlInfo = NULL;
    DWORD size = 0;

    TRACE("(%08x, %p, %d)\n", dwCertEncodingType, pbCrlEncoded,
     cbCrlEncoded);

    if ((dwCertEncodingType & CERT_ENCODING_TYPE_MASK) != X509_ASN_ENCODING)
    {
        SetLastError(E_INVALIDARG);
        return NULL;
    }
    ret = CryptDecodeObjectEx(dwCertEncodingType, X509_CERT_CRL_TO_BE_SIGNED,
     pbCrlEncoded, cbCrlEncoded, CRYPT_DECODE_ALLOC_FLAG, NULL,
     &crlInfo, &size);
    if (ret)
    {
        BYTE *data = NULL;

        crl = Context_CreateDataContext(sizeof(CRL_CONTEXT));
        if (!crl)
            goto end;
        data = CryptMemAlloc(cbCrlEncoded);
        if (!data)
        {
            CryptMemFree(crl);
            crl = NULL;
            goto end;
        }
        memcpy(data, pbCrlEncoded, cbCrlEncoded);
        crl->dwCertEncodingType = dwCertEncodingType;
        crl->pbCrlEncoded       = data;
        crl->cbCrlEncoded       = cbCrlEncoded;
        crl->pCrlInfo           = crlInfo;
        crl->hCertStore         = 0;
    }

end:
    return crl;
}