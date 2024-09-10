HRESULT
ToStringEnc(DWORD dwFlags, const BYTE *pbBinary, DWORD cbBinary, LPSTR *pszString)
{
	BOOL bRes = FALSE;
    HRESULT hRes=S_OK;
    DWORD cchString = 0;

	bRes = CryptBinaryToStringA(pbBinary, cbBinary, dwFlags, NULL, &cchString);
	if (!bRes){
        dprintf("[sync] send failed at CryptBinaryToString: %d\n", GetLastError());
        return E_FAIL;
    }

    *pszString = (LPSTR) malloc(cchString);

    if (*pszString==NULL){
        dprintf("[sync] failed at allocate buffer: %d\n", GetLastError());
        return E_FAIL;
    }

	bRes = CryptBinaryToStringA(pbBinary, cbBinary, dwFlags, *pszString, &cchString);
	if (!bRes){
        dprintf("[sync] failed at CryptBinaryToString: %d\n", GetLastError());
        if (*pszString)
        {
            free(*pszString);
            *pszString = NULL;
        }
        return E_FAIL;
    }

    /*
    CRYPT_STRING_NOCRLF 0x40000000
    Windows Server 2003 and Windows XP: This value is not supported
    */

    #if _NT_TARGET_VERSION_WINXPOR2K3
    trimcrlf(*pszString);
    #endif

    return hRes;
}