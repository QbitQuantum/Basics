static BOOL WINTRUST_GetSignedMsgFromPEFile(SIP_SUBJECTINFO *pSubjectInfo,
 DWORD *pdwEncodingType, DWORD dwIndex, DWORD *pcbSignedDataMsg,
 BYTE *pbSignedDataMsg)
{
    BOOL ret;
    WIN_CERTIFICATE *pCert = NULL;
    HANDLE file;

    TRACE("(%p %p %d %p %p)\n", pSubjectInfo, pdwEncodingType, dwIndex,
          pcbSignedDataMsg, pbSignedDataMsg);

    if(pSubjectInfo->hFile && pSubjectInfo->hFile!=INVALID_HANDLE_VALUE)
        file = pSubjectInfo->hFile;
    else
    {
        file = CreateFileW(pSubjectInfo->pwsFileName, GENERIC_READ,
                FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if(file == INVALID_HANDLE_VALUE)
            return FALSE;
    }
 
    if (!pbSignedDataMsg)
    {
        WIN_CERTIFICATE cert;

        /* app hasn't passed buffer, just get the length */
        ret = ImageGetCertificateHeader(file, dwIndex, &cert);
        if (ret)
        {
            switch (cert.wCertificateType)
            {
            case WIN_CERT_TYPE_X509:
            case WIN_CERT_TYPE_PKCS_SIGNED_DATA:
                *pcbSignedDataMsg = cert.dwLength;
                break;
            default:
                WARN("unknown certificate type %d\n", cert.wCertificateType);
                ret = FALSE;
            }
        }
    }
    else
    {
        DWORD len = 0;

        ret = ImageGetCertificateData(file, dwIndex, NULL, &len);
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
            goto error;
        pCert = HeapAlloc(GetProcessHeap(), 0, len);
        if (!pCert)
        {
            ret = FALSE;
            goto error;
        }
        ret = ImageGetCertificateData(file, dwIndex, pCert, &len);
        if (!ret)
            goto error;
        pCert->dwLength -= FIELD_OFFSET(WIN_CERTIFICATE, bCertificate);
        if (*pcbSignedDataMsg < pCert->dwLength)
        {
            *pcbSignedDataMsg = pCert->dwLength;
            SetLastError(ERROR_INSUFFICIENT_BUFFER);
            ret = FALSE;
        }
        else
        {
            memcpy(pbSignedDataMsg, pCert->bCertificate, pCert->dwLength);
            *pcbSignedDataMsg = pCert->dwLength;
            switch (pCert->wCertificateType)
            {
            case WIN_CERT_TYPE_X509:
                *pdwEncodingType = X509_ASN_ENCODING;
                break;
            case WIN_CERT_TYPE_PKCS_SIGNED_DATA:
                *pdwEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
                break;
            default:
                WARN("don't know what to do for encoding type %d\n",
                 pCert->wCertificateType);
                *pdwEncodingType = 0;
                ret = FALSE;
            }
        }
    }
error:
    if(pSubjectInfo->hFile != file)
        CloseHandle(file);
    HeapFree(GetProcessHeap(), 0, pCert);
    return ret;
}