static BOOL CRYPT_QueryEmbeddedMessageObject(DWORD dwObjectType,
 const void *pvObject, DWORD dwExpectedContentTypeFlags,
 DWORD *pdwMsgAndCertEncodingType, DWORD *pdwContentType,
 HCERTSTORE *phCertStore, HCRYPTMSG *phMsg)
{
    HANDLE file;
    BOOL ret = FALSE;

    if (dwObjectType != CERT_QUERY_OBJECT_FILE)
    {
        FIXME("don't know what to do for type %d embedded signed messages\n",
         dwObjectType);
        SetLastError(E_INVALIDARG);
        return FALSE;
    }
    file = CreateFileW((LPCWSTR)pvObject, GENERIC_READ, FILE_SHARE_READ,
     NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE)
    {
        DWORD len;

        ret = ImageGetCertificateData(file, 0, NULL, &len);
        if (ret)
        {
            WIN_CERTIFICATE *winCert = HeapAlloc(GetProcessHeap(), 0, len);

            if (winCert)
            {
                ret = ImageGetCertificateData(file, 0, winCert, &len);
                if (ret)
                {
                    CERT_BLOB blob = { winCert->dwLength,
                     winCert->bCertificate };

                    ret = CRYPT_QueryMessageObject(CERT_QUERY_OBJECT_BLOB,
                     &blob, CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED,
                     pdwMsgAndCertEncodingType, NULL, phCertStore, phMsg);
                    if (ret && pdwContentType)
                        *pdwContentType = CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED;
                }
                HeapFree(GetProcessHeap(), 0, winCert);
            }
        }
        CloseHandle(file);
    }
    TRACE("returning %d\n", ret);
    return ret;
}