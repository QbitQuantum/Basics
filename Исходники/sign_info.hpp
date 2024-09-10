inline SYSTEMTIME ZLSignInfo::_ReadSigningTime(PCMSG_SIGNER_INFO pMsgSignerInfoOfTimestamp)
{
    SYSTEMTIME st = {0};

    for (DWORD n = 0; n < pMsgSignerInfoOfTimestamp->AuthAttrs.cAttr; ++n)
    {
        if (lstrcmpA(szOID_RSA_signingTime, pMsgSignerInfoOfTimestamp->AuthAttrs.rgAttr[n].pszObjId) == 0)
        {
            FILETIME ftSignInfo = {0};
            DWORD dwSize = sizeof(FILETIME);

            if (::CryptDecodeObject(
                X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                szOID_RSA_signingTime,
                pMsgSignerInfoOfTimestamp->AuthAttrs.rgAttr[n].rgValue[0].pbData,
                pMsgSignerInfoOfTimestamp->AuthAttrs.rgAttr[n].rgValue[0].cbData,
                0,
                (PVOID)&ftSignInfo,
                &dwSize))
            {
                FILETIME ftTmp = {0};
                ::FileTimeToLocalFileTime(&ftSignInfo, &ftTmp);
                ::FileTimeToSystemTime(&ftTmp, &st);
            }

            break;
        }
    }
    return st;
}